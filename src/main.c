#include <stdio.h>
#include <platform_sdl.h>
#include <wf_common.h>
#include <math.h>

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

	while (!input.quit) {
		wf_platform_poll_input(platform, &input);
		float dt = wf_platform_get_delta_time(platform);
		time += dt;

		uint8_t r = (uint8_t)(40.0f + 30.0f * sinf(time * 2.0f));
		uint8_t g = 20;
		uint8_t b = 40;

		wf_platform_clear(platform, r, g, b);
		wf_platform_present(platform);
	}

	wf_platform_shutdown(platform);

	return 0;
}
