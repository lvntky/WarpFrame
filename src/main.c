#include <stdio.h>
#include <platform_sdl.h>
#include <wf_common.h>
#include <math.h>
#include <c_renderer.h>
#include <c_rasterizer.h>
#include <m_type.h>
#include <string.h>
#include <m_util.h>
#include <wf_obj_parser.h>
#include <stdlib.h>

/*
  temp code start
 */

static vec4f_t rotate_y(vec4f_t v, float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	vec4f_t out = v;

	out.x = v.x * c + v.z * s;
	out.z = -v.x * s + v.z * c;

	return out;
}

static uint32_t random_color(void)
{
	uint8_t r = 64 + rand() % 192;
	uint8_t g = 64 + rand() % 192;
	uint8_t b = 64 + rand() % 192;

	return ((uint32_t)r << 16) | ((uint32_t)g << 8) | ((uint32_t)b);
}

/*
  temp code end
 */

void object_to_screen(vec4f_t *normalized_obj_vertices, int *faces,
		      int vertex_count, int face_count, int *out_count,
		      float angle, c_rasterizer_triangle_t *triangle_list)
{
	c_rasterizer_vertex_t screen_vertex_list[vertex_count];

	for (int r = 0; r < vertex_count; r++) {
		normalized_obj_vertices[r] =
			rotate_y(normalized_obj_vertices[r], angle);
	}

	vec4f_t *transformed_obj_vertices = c_renderer_model_transform(
		normalized_obj_vertices, 0.0, 0.0, 0.3, vertex_count);

	c_renderer_projected_vertex_t projected_vertex_list[vertex_count];

	for (int i = 0; i < vertex_count; i++) {
		c_renderer_create_projected_vertex(transformed_obj_vertices[i],
						   &projected_vertex_list[i]);
	}

	for (int j = 0; j < vertex_count; j++) {
		screen_vertex_list[j] = c_renderer_create_viewport_vertex(
			projected_vertex_list[j]);
	}

	int triangle_count = 0;

	for (int f = 0; f < face_count; f++) {
		int i0 = faces[f * 3 + 0];
		int i1 = faces[f * 3 + 1];
		int i2 = faces[f * 3 + 2];

		c_rasterizer_vertex_t a = screen_vertex_list[i0];
		c_rasterizer_vertex_t b = screen_vertex_list[i1];
		c_rasterizer_vertex_t c = screen_vertex_list[i2];

		if (!c_renderer_backface_area(a, b, c)) {
			triangle_list[triangle_count++] =
				(c_rasterizer_triangle_t){ a, b, c,
							   random_color() };
		}
	}

	*out_count = triangle_count;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stdout, "%s running without loaded object", argv[0]);
	}

	const wf_obj_parsed_t *obj = wf_obj_parse(argv[1]);

	wf_platform_t *platform = NULL;

	if (!wf_platform_init(&platform, WF_INTERNAL_WIDTH, WF_INTERNAL_HEIGHT,
			      WF_WINDOW_SCALE)) {
		fprintf(stderr, "Failed to initialize WarpFrame platform.\n");
		return 1;
	}

	wf_input_t input = { 0 };
	float time = 0.0f;

	c_renderer_t *renderer;
	c_renderer_init(&renderer);

	int counter = 0;

	int triangle_count = 0;
	vec4f_t *normalized_obj_vertices = wf_obj_normalize(obj);
	int vertex_count = obj->vertex_count;
	int face_count = obj->face_count;
	int *faces = obj->faces;
	float rotation_angle = 0.0f;

	c_rasterizer_triangle_t *tri =
		malloc(vertex_count * sizeof(c_rasterizer_triangle_t));
	while (!input.quit) {
		c_renderer_clean(renderer);
		wf_platform_poll_input(&input);
		float dt = wf_platform_get_delta_time(platform);
		time += dt;

		object_to_screen(normalized_obj_vertices, faces,
				       vertex_count, face_count,
						 &triangle_count, rotation_angle + 0.05f, tri);

		for (int i = 0; i < triangle_count; i++) {
			c_rasterizer_draw_triangle_solid(renderer, tri[i]);
		}
		//c_rasterizer_draw_triangle_solid(renderer, tri, 0xFF0000);

		wf_platform_present(platform, renderer->color_buffer);

		counter += 1;
	}

	wf_platform_shutdown(platform);

	return 0;
}
