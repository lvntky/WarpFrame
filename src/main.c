#include <stdio.h>
#include <platform_sdl.h>
#include <wf_common.h>
#include <math.h>
#include <c_renderer.h>
#include <c_rasterizer.h>
#include <m_type.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stdout, "%s running without loaded object", argv[0]);
	}

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

	c_rasterizer_vertex_t d = { 160, 20, 0};
	c_rasterizer_vertex_t e = { 45, 80, 0};
	c_rasterizer_vertex_t f = { 160, 80, 0};

	c_rasterizer_vertex_t a = { 150, 20, 0};
	c_rasterizer_vertex_t b = { 30, 60, 0};
	c_rasterizer_vertex_t c = { 160, 80, 0};

	c_rasterizer_triangle_t triangle1 = { d, e, f, 0 };
	c_rasterizer_triangle_t triangle2 = { a, b, c, 0 };

	c_rasterizer_draw_triangle_solid(renderer, triangle1, 0x0000FF);
	c_rasterizer_draw_triangle_solid(renderer, triangle2, 0xFF00FF);
	c_rasterizer_draw_triangle_bounding_box_points(renderer, triangle1);
	c_rasterizer_draw_triangle_bounding_box_points(renderer, triangle2);

	int counter = 0;

	while (!input.quit) {
		wf_platform_poll_input(&input);
		float dt = wf_platform_get_delta_time(platform);
		time += dt;
		//fprintf(stdout, "Delta Time: %f\n", time);

		//		wf_platform_clear(platform, r, g, b);

		wf_platform_present(platform, renderer->color_buffer);
		counter += 1;
	}

	wf_platform_shutdown(platform);

	return 0;
}
