#ifndef C_RENDERER_H_
#define C_RENDERER_H_

#include <stdint.h>
#include <c_rasterizer_type.h>

typedef struct c_renderer {
	uint32_t *framebuffer;
	uint32_t *color_buffer;
	float *depth_buffer;
	uint32_t data_len;
} c_renderer_t;

typedef struct c_renderer_ndc_vertex {
	float x;
	float y;
	float z;
} c_renderer_ndc_vertex_t;

int c_renderer_init(c_renderer_t **renderer);
void c_renderer_shutdown(c_renderer_t *renderer);
void c_renderer_clean(c_renderer_t *renderer);
c_rasterizer_vertex_t c_renderer_viewport_transformation(c_renderer_ndc_vertex_t v);

#endif //C_RENDERER_H_
