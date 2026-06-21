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

void c_renderer_model_transform(wf_obj_parsed_t *obj, float x, float y, float z)
{
	for (int i = 0; i < obj->vertex_count; i++) {
		obj->vertices[i].x += x;
		obj->vertices[i].y += y;
		obj->vertices[i].z += z;
	}
}

bool c_renderer_create_projected_vertex(vec4f_t v,
				 c_renderer_projected_vertex_t *vertex)
{
	if (v.z < 0.1f) {
		return false;
	}

	vertex->x = v.x / v.z;
	vertex->y = v.y / v.z;
	vertex->z = v.z;

	return vertex;
}

c_rasterizer_vertex_t
c_renderer_create_viewport_vertex(c_renderer_projected_vertex_t projected)
{
	int screen_x = (projected.x + 1.0f) * 0.5f * WF_INTERNAL_WIDTH;
	int screen_y = (1.0f - projected.y) * 0.5f * WF_INTERNAL_HEIGHT;
	float screen_z = projected.z;

	return (c_rasterizer_vertex_t){
		.x = screen_x,
		.y = screen_y,
		.z = screen_z,
	};
}
