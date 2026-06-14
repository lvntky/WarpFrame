#include <c_renderer.h>
#include <wf_common.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int c_renderer_init(c_renderer_t **renderer)
{
	c_renderer_t *irnd = malloc(sizeof(c_renderer_t));
	irnd->data_len = WF_INTERNAL_WIDTH * WF_INTERNAL_HEIGHT;

	irnd->framebuffer = calloc(irnd->data_len, sizeof(uint32_t));
	irnd->color_buffer = calloc(irnd->data_len, sizeof(uint32_t));
	irnd->depth_buffer = calloc(irnd->data_len, sizeof(uint32_t));

	memset(irnd->depth_buffer, INT_MAX,
	       irnd->data_len * (sizeof(uint32_t)));

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
void c_renderer_clean(c_renderer_t *renderer)
{
	memset(renderer->depth_buffer, INT_MAX,
	       renderer->data_len * (sizeof(uint32_t)));

	
	memset(renderer->color_buffer, 0x000000,
	       renderer->data_len * (sizeof(uint32_t)));
}
