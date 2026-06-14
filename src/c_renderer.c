#include <c_renderer.h>
#include <wf_common.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

int c_renderer_init(c_renderer_t **renderer)
{
	c_renderer_t *irnd = malloc(sizeof(c_renderer_t));
	irnd->data_len = WF_INTERNAL_WIDTH * WF_INTERNAL_HEIGHT;

	irnd->framebuffer = calloc(irnd->data_len, sizeof(uint32_t));
	irnd->color_buffer = calloc(irnd->data_len, sizeof(uint32_t));
	irnd->depth_buffer = malloc(irnd->data_len * sizeof(float));

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
	for (int i = 0; i < renderer->data_len; i++) {
		renderer->color_buffer[i] = 0x000000;
		renderer->depth_buffer[i] = FLT_MAX;
	}
}

c_rasterizer_vertex_t
c_renderer_viewport_transformation(c_renderer_ndc_vertex_t v)
{
	c_rasterizer_vertex_t out;
	out.x = (int)((v.x + 1.0f) * 0.5f * (WF_INTERNAL_WIDTH - 1));
	out.y = (int)((1.0f - v.y) * 0.5f * (WF_INTERNAL_HEIGHT - 1));
	out.z = v.z;

	return out;
}
