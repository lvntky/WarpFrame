#include <stdio.h>
#include <platform_sdl.h>
#include <wf_common.h>
#include <math.h>
#include <c_renderer.h>
#include <c_rasterizer.h>
#include <m_type.h>

int main(int argc, char *argv[])
{
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

	// test gradient on renderer
	for (int i = 0; i < WF_INTERNAL_WIDTH * WF_INTERNAL_HEIGHT; i++) {
		renderer->color_buffer[i] = 0xFF0000;
		//		renderer->color_buffer[i] = 0x000000;
	}

	vec2i_t d = { 160, 20 };
	vec2i_t e = { 45, 80 };
	vec2i_t f = { 160, 80 };

	vec2i_t a = { 150, 20 };
	vec2i_t b = { 30, 60 };
	vec2i_t c = { 160, 80 };

	c_rasterizer_draw_triangle_solid(renderer, d, e, f, 0x0000FF);
	c_rasterizer_draw_triangle_solid(renderer, a, b, c, 0xFF00FF);
	c_rasterizer_draw_triangle_bounding_box_points(renderer, d, e, f);
	c_rasterizer_draw_triangle_bounding_box_points(renderer, a, b, c);

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
