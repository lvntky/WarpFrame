#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <c_rasterizer.h>
#include <wf_common.h>
#include <m_type.h>
#include <m_util.h>
#include <limits.h>
#include <wf_texture.h>
#include <wf_tile_manager.h>

/** Locals */
static wf_grid_t c_rasterizer_grid;
static wf_grid_t *c_rasterizer_grid_ptr;

typedef struct barycentric {
	float l0;
	float l1;
	float l2;
} barycentric_t;

static int min(int a, int b, int c)
{
	int pre = a < b ? a : b;
	return pre < c ? pre : c;
}

static int max(int a, int b, int c)
{
	int pre = a > b ? a : b;
	return pre > c ? pre : c;
}

//E_ab(P) = (Vb.x - Va.x) * (P.y - Va.y) - (Vb.y - Va.y) * (P.x - Va.x)
static int edge_function(c_rasterizer_vertex_t a, c_rasterizer_vertex_t b,
			 c_rasterizer_vertex_t p)
{
	return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

static barycentric_t barycentric_coordinate(c_rasterizer_triangle_t triangle,
					    c_rasterizer_vertex_t p)
{
	c_rasterizer_vertex_t a = triangle.a;
	c_rasterizer_vertex_t b = triangle.b;
	c_rasterizer_vertex_t c = triangle.c;

	int area = edge_function(a, b, c);

	if (area == 0) {
		return (barycentric_t){ 0.0f, 0.0f, 0.0f }; // degenerate
	}
	int wa = edge_function(b, c, p); // opposite a
	int wb = edge_function(c, a, p); // opposite b
	int wc = edge_function(a, b, p); // opposite c

	float inv_area = 1.0f / (float)area;
	return (barycentric_t){ wa * inv_area, wb * inv_area, wc * inv_area };
}

static float calculate_pixel_depth(c_rasterizer_triangle_t triangle,
				   barycentric_t bc)
{
	return bc.l0 * (float)triangle.a.z + bc.l1 * (float)triangle.b.z +
	       bc.l2 * (float)triangle.c.z;
}

static bool is_point_inside_triange(c_rasterizer_triangle_t triangle,
				    c_rasterizer_vertex_t p)
{
	c_rasterizer_vertex_t a = triangle.a;
	c_rasterizer_vertex_t b = triangle.b;
	c_rasterizer_vertex_t c = triangle.c;

	int w0 = edge_function(a, b, p);
	int w1 = edge_function(b, c, p);
	int w2 = edge_function(c, a, p);

	bool all_neg = (w0 <= 0 && w1 <= 0 && w2 <= 0);
	bool all_pos = (w0 >= 0 && w1 >= 0 && w2 >= 0);

	return all_neg || all_pos;
}

// todo: temporart will delete
float normalize_depth(float z, float near, float far)
{
	float t = (z - near) / (far - near);

	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;

	return t;
}

uint32_t color_from_depth(float z)
{
	z = normalize_depth(z, 0.1f, 0.8f);
	if (z < 0.0f)
		z = 0.0f;
	if (z > 1.0f)
		z = 1.0f;

	uint8_t shade = (uint8_t)((1.0f - z) * 255.0f);

	return 0xff000000 | (shade << 16) | (shade << 8) | shade;
}

// temprary ends here

void c_rasterizer_put_pixel(c_renderer_t *renderer, int x, int y,
			    uint32_t color)
{
	if (x < 0 || x >= WF_INTERNAL_WIDTH) {
		return;
	}
	if (y < 0 || y >= WF_INTERNAL_HEIGHT) {
		return;
	}
	renderer->color_buffer[y * WF_INTERNAL_WIDTH + x] = color;
}

bounding_box_t
c_rasterizer_triange_calculate_bounding_box(c_rasterizer_triangle_t triangle)
{
	c_rasterizer_vertex_t a = triangle.a;
	c_rasterizer_vertex_t b = triangle.b;
	c_rasterizer_vertex_t c = triangle.c;

	int x_max = max(a.x, b.x, c.x);
	int x_min = min(a.x, b.x, c.x);
	int y_max = max(a.y, b.y, c.y);
	int y_min = min(a.y, b.y, c.y);
	vec2i_t tl = { x_min, y_min };
	vec2i_t tr = { x_max, y_min };
	vec2i_t bl = { x_min, y_max };
	vec2i_t br = { x_max, y_max };
	bounding_box_t box = { tl, tr, bl, br };
	return box;
}

float interpolate_texture_u(c_rasterizer_triangle_t tri, barycentric_t pbar)
{
	return tri.a.u * pbar.l0 + tri.b.u * pbar.l1 + tri.c.u * pbar.l2;
}

float interpolate_texture_v(c_rasterizer_triangle_t tri, barycentric_t pbar)
{
	return tri.a.v * pbar.l0 + tri.b.v * pbar.l1 + tri.c.v * pbar.l2;
}

void project_polygon(vec2i_t *vertices, size_t count, vec2i_t axis, int *min,
		     int *max)
{
	*min = INT_MAX;
	*max = INT_MIN;

	for (size_t i = 0; i < count; ++i) {
		int projection = m_vec2i_dot(vertices[i], axis);

		if (projection < *min)
			*min = projection;

		if (projection > *max)
			*max = projection;
	}
}

static bool sat_collision_2d(wf_tile_t *tile, c_rasterizer_triangle_t *triangle)
{
	vec2i_t axes[5];

	/* Tile axes */
	axes[0] = (vec2i_t){ .x = 1, .y = 0 };

	axes[1] = (vec2i_t){ .x = 0, .y = 1 };

	/* Triangle edges */
	vec2i_t edge_a = m_vec2i_edge(
		(vec2i_t){ .x = triangle->a.x, .y = triangle->a.y },
		(vec2i_t){ .x = triangle->b.x, .y = triangle->b.y });

	vec2i_t edge_b = m_vec2i_edge(
		(vec2i_t){ .x = triangle->b.x, .y = triangle->b.y },
		(vec2i_t){ .x = triangle->c.x, .y = triangle->c.y });

	vec2i_t edge_c = m_vec2i_edge(
		(vec2i_t){ .x = triangle->c.x, .y = triangle->c.y },
		(vec2i_t){ .x = triangle->a.x, .y = triangle->a.y });

	/* Triangle axes */
	axes[2] = (vec2i_t){ .x = -edge_a.y, .y = edge_a.x };

	axes[3] = (vec2i_t){ .x = -edge_b.y, .y = edge_b.x };

	axes[4] = (vec2i_t){ .x = -edge_c.y, .y = edge_c.x };

	vec2i_t tile_vertices[4] = {
		{ .x = tile->x, .y = tile->y },
		{ .x = tile->x + WF_TILE_SIZE, .y = tile->y },
		{ .x = tile->x + WF_TILE_SIZE, .y = tile->y + WF_TILE_SIZE },
		{ .x = tile->x, .y = tile->y + WF_TILE_SIZE }
	};
	vec2i_t triangle_vertices[3] = {
		{ .x = triangle->a.x, .y = triangle->a.y },
		{ .x = triangle->b.x, .y = triangle->b.y },
		{ .x = triangle->c.x, .y = triangle->c.y }
	};

	for (size_t i = 0; i < 5; ++i) {
		int tile_min, tile_max;
		int triangle_min, triangle_max;

		project_polygon(tile_vertices, 4, axes[i], &tile_min,
				&tile_max);

		project_polygon(triangle_vertices, 3, axes[i], &triangle_min,
				&triangle_max);

		/* Separating axis found */
		if (tile_max < triangle_min || triangle_max < tile_min) {
			return false;
		}
	}

	return true;
}

void c_tile_grid_triangle_bind(wf_grid_t *grid, bounding_box_t box,
			       c_rasterizer_triangle_t *tri)
{
	int cols = wf_tile_col_num(WF_INTERNAL_WIDTH);
	int rows = wf_tile_row_num(WF_INTERNAL_HEIGHT);

	/*
     * Clamp bounding box to screen.
     */
	int x_min = box.top_left.x;

	if (x_min < 0)
		x_min = 0;

	int x_max = box.top_right.x;

	if (x_max >= WF_INTERNAL_WIDTH)
		x_max = WF_INTERNAL_WIDTH - 1;

	int y_min = box.top_left.y;

	if (y_min < 0)
		y_min = 0;

	int y_max = box.bottom_left.y;

	if (y_max >= WF_INTERNAL_HEIGHT)
		y_max = WF_INTERNAL_HEIGHT - 1;

	/*
     * Completely outside screen.
     */
	if (x_min > x_max || y_min > y_max)
		return;

	int col_min = x_min / WF_TILE_SIZE;
	int col_max = x_max / WF_TILE_SIZE;

	int row_min = y_min / WF_TILE_SIZE;
	int row_max = y_max / WF_TILE_SIZE;

	/*
     * Extra safety.
     */
	if (col_min < 0)
		col_min = 0;

	if (col_max >= cols)
		col_max = cols - 1;

	if (row_min < 0)
		row_min = 0;

	if (row_max >= rows)
		row_max = rows - 1;

	for (int row = row_min; row <= row_max; row++) {
		for (int col = col_min; col <= col_max; col++) {
			int index = row * cols + col;
			if (sat_collision_2d(&grid->tiles[index], tri)) {
				grid->tiles[index].tri = tri;
			}
		}
	}
}

static void c_rasterizer_debug_draw_grid_mesh(c_renderer_t *renderer,
					      wf_grid_t *grid)
{
	uint32_t color = 0x00FF00;

	for (int i = 0; i < grid->count; i++) {
		if (grid->tiles[i].tri != NULL) {
			int x0 = grid->tiles[i].x;
			int y0 = grid->tiles[i].y;
			int x1 = x0 + WF_TILE_SIZE - 1;
			int y1 = y0 + WF_TILE_SIZE - 1;

			if (x1 >= WF_INTERNAL_WIDTH) {
				x1 = WF_INTERNAL_WIDTH - 1;
			}
			if (y1 >= WF_INTERNAL_HEIGHT) {
				y1 = WF_INTERNAL_HEIGHT - 1;
			}

			for (int x = x0; x <= x1; x++) {
				c_rasterizer_put_pixel(renderer, x, y0, color);
				c_rasterizer_put_pixel(renderer, x, y1, color);
			}
			for (int y = y0; y <= y1; y++) {
				c_rasterizer_put_pixel(renderer, x0, y, color);
				c_rasterizer_put_pixel(renderer, x1, y, color);
			}
		}
	}
}

static void c_rasterizer_draw_tile(c_renderer_t *renderer, wf_tile_t *tile,
				   c_rasterizer_triangle_t *triangle,
				   wf_texture_t *texture)
{
	int x_start = tile->x;
	int y_start = tile->y;

	int x_end = x_start + WF_TILE_SIZE;
	int y_end = y_start + WF_TILE_SIZE;

	if (x_end > WF_INTERNAL_WIDTH)
		x_end = WF_INTERNAL_WIDTH;

	if (y_end > WF_INTERNAL_HEIGHT)
		y_end = WF_INTERNAL_HEIGHT;

	for (int y = y_start; y < y_end; y++) {
		uint32_t *row = &renderer->color_buffer[y * WF_INTERNAL_WIDTH];

		float *renderer_depth =
			&renderer->depth_buffer[y * WF_INTERNAL_WIDTH];

		for (int x = x_start; x < x_end; x++) {
			c_rasterizer_vertex_t p = { x, y, 0.0f };

			if (!is_point_inside_triange(*triangle, p))
				continue;

			barycentric_t pbar =
				barycentric_coordinate(*triangle, p);

			p.z = calculate_pixel_depth(*triangle, pbar);

			float texture_pu =
				interpolate_texture_u(*triangle, pbar);

			float texture_pv =
				interpolate_texture_v(*triangle, pbar);

			int tex_u = texture_pu * texture->width;

			int tex_v = texture_pv * texture->height;

			if (tex_u < 0)
				tex_u = 0;

			if (tex_v < 0)
				tex_v = 0;

			if (tex_u >= texture->width)
				tex_u = texture->width - 1;

			if (tex_v >= texture->height)
				tex_v = texture->height - 1;

			if (p.z < renderer_depth[x]) {
				renderer_depth[x] = p.z;

				row[x] = texture->data[tex_v * texture->width +
						       tex_u];
			}
		}
	}
}

void c_rasterizer_draw_triangle_solid(c_renderer_t *renderer,
				      c_rasterizer_triangle_t triangle,
				      wf_texture_t *texture)
{
	bounding_box_t box =
		c_rasterizer_triange_calculate_bounding_box(triangle);

	c_rasterizer_grid =
		wf_tile_create_grid(WF_INTERNAL_WIDTH, WF_INTERNAL_HEIGHT);
	c_rasterizer_grid_ptr = &c_rasterizer_grid;

	c_tile_grid_triangle_bind(c_rasterizer_grid_ptr, box, &triangle);

	int cols = wf_tile_col_num(WF_INTERNAL_WIDTH);

	int rows = wf_tile_row_num(WF_INTERNAL_HEIGHT);

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			int index = row * cols + col;

			wf_tile_t *tile = &c_rasterizer_grid_ptr->tiles[index];

			if (tile->tri == NULL)
				continue;

			c_rasterizer_draw_tile(renderer, tile, tile->tri,
					       texture);
		}
	}

#ifdef WF_DEBUG
	c_rasterizer_debug_draw_grid_mesh(renderer, c_rasterizer_grid_ptr);
#endif
	wf_tile_destroy_tile(c_rasterizer_grid_ptr->tiles);
}

void c_rasterizer_draw_triangle_bounding_box_points(
	c_renderer_t *renderer, c_rasterizer_triangle_t triangle)
{
	bounding_box_t box =
		c_rasterizer_triange_calculate_bounding_box(triangle);

	c_rasterizer_put_pixel(renderer, box.top_left.x, box.top_left.y,
			       0x00FF00);
	c_rasterizer_put_pixel(renderer, box.top_right.x, box.top_right.y,
			       0x00FF00);
	c_rasterizer_put_pixel(renderer, box.bottom_left.x, box.bottom_left.y,
			       0x00FF00);
	c_rasterizer_put_pixel(renderer, box.bottom_right.x, box.bottom_right.y,
			       0x00FF00);
}
