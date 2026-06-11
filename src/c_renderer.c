#include <c_renderer.h>
#include <wf_common.h>
#include <stdlib.h>

int c_renderer_init(c_renderer_t **renderer)
{
	c_renderer_t *irnd = malloc(sizeof(c_renderer_t));

	irnd->framebuffer = calloc(WF_INTERNAL_WIDTH * WF_INTERNAL_HEIGHT,
				    sizeof(uint32_t));
irnd->color_buffer = calloc(WF_INTERNAL_WIDTH * WF_INTERNAL_HEIGHT,
				    sizeof(uint32_t));
irnd->depth_buffer = calloc(WF_INTERNAL_WIDTH * WF_INTERNAL_HEIGHT,
				    sizeof(uint32_t));
irnd->data_len = WF_INTERNAL_WIDTH * WF_INTERNAL_HEIGHT;
	
	*renderer = irnd;
	return 0;
}

void c_renderer_shutdown(c_renderer_t *renderer)
{
	if (renderer->framebuffer != NULL) {
		free(renderer->framebuffer);
	}

	if (renderer->color_buffer != NULL) {
		free(renderer->color_buffer);
	}

	if (renderer->depth_buffer != NULL) {
		free(renderer->depth_buffer);
	}

	if (renderer != NULL) {
		free(renderer);
	}
}
