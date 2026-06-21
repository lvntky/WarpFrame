#ifndef C_RENDERER_H_
#define C_RENDERER_H_

#include <stdint.h>
#include <c_rasterizer_type.h>
#include <wf_obj_parser.h>
#include <stdbool.h>

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

typedef struct c_renderer_projected_vertex {
	float x;
	float y;
	float z;
} c_renderer_projected_vertex_t;

int c_renderer_init(c_renderer_t **renderer);
void c_renderer_shutdown(c_renderer_t *renderer);
void c_renderer_clean(c_renderer_t *renderer);
c_rasterizer_vertex_t
c_renderer_viewport_transformation(c_renderer_ndc_vertex_t v);
void c_renderer_model_transform(wf_obj_parsed_t *obj, float x, float y,
				float z);

bool c_renderer_create_projected_vertex(vec4f_t v, c_renderer_projected_vertex_t* vertex);

c_rasterizer_vertex_t c_renderer_create_viewport_vertex(c_renderer_projected_vertex_t projected);

bool c_renderer_backface_area(c_rasterizer_vertex_t a, c_rasterizer_vertex_t b, c_rasterizer_vertex_t c);

#endif //C_RENDERER_H_
