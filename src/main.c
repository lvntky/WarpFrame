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

	c_renderer_ndc_vertex_t ndc_v[] = {
		{ 0.0f, 0.5f, 5.0f },
		{ -0.5f, -0.5f, 5.0f },
		{ 0.5f, -0.5f, 10.0f },
	};

	int counter = 0;

	while (!input.quit) {
		c_renderer_clean(renderer);
		wf_platform_poll_input(&input);
		float dt = wf_platform_get_delta_time(platform);
		time += dt;

		c_rasterizer_triangle_t tri = {
			c_renderer_viewport_transformation(ndc_v[0]),
			c_renderer_viewport_transformation(ndc_v[1]),
			c_renderer_viewport_transformation(ndc_v[2])
		};

		c_rasterizer_draw_triangle_solid(renderer, tri, 0xFF0000);

		wf_platform_present(platform, renderer->color_buffer);

		counter += 1;
	}

	wf_platform_shutdown(platform);

	return 0;
}
