#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <c_rasterizer.h>
#include <wf_common.h>
#include <m_type.h>
#include <m_util.h>

typedef struct bounding_box_t {
	vec2i_t top_left;
	vec2i_t top_right;
	vec2i_t bottom_left;
	vec2i_t bottom_right;
} bounding_box_t;

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

static int edge_function(vec2i_t a, vec2i_t b, vec2i_t p)
{
	vec2i_t ab = { (b.x - a.x), (b.y - a.y) };
	vec2i_t ap = { (p.x - a.x), (p.y - a.y) };
	return m_det2i(ab, ap);
}

static bool is_point_inside_triange(trianglei_t triangle, vec2i_t p)
{
	//TODO: triangle to vector2i convertion function
	vec2i_t a = triangle.pa;
	vec2i_t b = triangle.pb;
	vec2i_t c = triangle.pc;

	int w0 = edge_function(a, b, p);
	int w1 = edge_function(b, c, p);
	int w2 = edge_function(c, a, p);
	bool all_neg = (w0 <= 0 && w1 <= 0 && w2 <= 0);
	bool all_pos = (w0 >= 0 && w1 >= 0 && w2 >= 0);
	return all_neg || all_pos;
}

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

bounding_box_t c_rasterizer_triange_calculate_bounding_box(trianglei_t triangle)
{
	vec2i_t a = triangle.pa;
	vec2i_t b = triangle.pb;
	vec2i_t c = triangle.pc;

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

void c_rasterizer_draw_triangle_solid(c_renderer_t *renderer,
				      trianglei_t triangle, uint32_t color)
{
	bounding_box_t box =
		c_rasterizer_triange_calculate_bounding_box(triangle);

	int x_start = box.top_left.x;
	int x_end = box.top_right.x;
	int y_start = box.top_left.y;
	int y_end = box.bottom_left.y;

	if (x_start < 0) {
		x_start = 0;
	}
	if (y_start < 0) {
		y_start = 0;
	}
	if (x_end >= WF_INTERNAL_WIDTH) {
		x_end = WF_INTERNAL_WIDTH - 1;
	}
	if (y_end >= WF_INTERNAL_HEIGHT) {
		y_end = WF_INTERNAL_HEIGHT - 1;
	}

	for (int y = y_start; y <= y_end; y++) {
		uint32_t *row = &renderer->color_buffer[y * WF_INTERNAL_WIDTH];
		for (int x = x_start; x <= x_end; x++) {
			vec2i_t p = { x, y };
			if (is_point_inside_triange(triangle, p)) {
				row[x] = color;
			}
		}
	}
}

void c_rasterizer_draw_triangle_bounding_box_points(c_renderer_t *renderer,
						    trianglei_t triangle)
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
