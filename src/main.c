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

static c_rasterizer_triangle_t *object_to_screen(wf_obj_parsed_t *obj)
{
	c_rasterizer_vertex_t screen_vertex_list[obj->vertex_count];
	c_rasterizer_triangle_t *triangle_list =
		malloc(sizeof(c_rasterizer_triangle_t) * obj->face_count);

	wf_obj_normalize(obj);
	c_renderer_model_transform(obj, 0.0, 0.0, 5.0);

	c_renderer_projected_vertex_t projected_vertex_list[obj->vertex_count];

	for (int i = 0; i < obj->vertex_count; i++) {
		c_renderer_create_projected_vertex(obj->vertices[i],
						   &projected_vertex_list[i]);
	}

	for (int j = 0; j < obj->vertex_count; j++) {
		screen_vertex_list[j] = c_renderer_create_viewport_vertex(
			projected_vertex_list[j]);
	}

	int triangle_count = 0;

	for (int f = 0; f < obj->face_count; f++) {
		int i0 = obj->faces[f * 3 + 0];
		int i1 = obj->faces[f * 3 + 1];
		int i2 = obj->faces[f * 3 + 2];

		c_rasterizer_vertex_t a = screen_vertex_list[i0];
		c_rasterizer_vertex_t b = screen_vertex_list[i1];
		c_rasterizer_vertex_t c = screen_vertex_list[i2];

		triangle_list[f] =
			(c_rasterizer_triangle_t){ a, b, c, 0x00FF00 };
	}

	return triangle_list;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stdout, "%s running without loaded object", argv[0]);
	}

	wf_obj_parsed_t *obj = wf_obj_parse(argv[1]);

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

	c_rasterizer_triangle_t *tri = object_to_screen(obj);

	while (!input.quit) {
		c_renderer_clean(renderer);
		wf_platform_poll_input(&input);
		float dt = wf_platform_get_delta_time(platform);
		time += dt;

		for (int i = 0; i < obj->face_count; i++) {
			c_rasterizer_draw_triangle_solid(renderer, tri[i],
							 0xFF00FF);
		}
		//c_rasterizer_draw_triangle_solid(renderer, tri, 0xFF0000);

		wf_platform_present(platform, renderer->color_buffer);

		counter += 1;
	}

	wf_platform_shutdown(platform);

	return 0;
}
