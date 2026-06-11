#include <stdio.h>
#include <platform_sdl.h>
#include <wf_common.h>
#include <math.h>
#include <c_renderer.h>

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

	while (!input.quit) {
		wf_platform_poll_input(&input);
		float dt = wf_platform_get_delta_time(platform);
		time += dt;
		//fprintf(stdout, "Delta Time: %f\n", time);

		//		wf_platform_clear(platform, r, g, b);
		wf_platform_present(platform, renderer->color_buffer);
	}

	wf_platform_shutdown(platform);

	return 0;
}
