#ifndef C_RASTERIZER_H_
#define C_RASTERIZER_H_

#include <c_renderer.h>
#include <m_type.h>

typedef struct bounding_box_t bounding_box_t;

void c_rasterizer_put_pixel(c_renderer_t *renderer, int x, int y,
			    uint32_t color);
void c_rasterizer_draw_triangle_solid(c_renderer_t *renderer, vec2i_t a,
				      vec2i_t b, vec2i_t c, uint32_t color);
bounding_box_t c_rasterizer_triange_calculate_bounding_box(vec2i_t a, vec2i_t b, vec2i_t c);
void c_rasterizer_draw_triangle_bounding_box_points(c_renderer_t *renderer, vec2i_t a, vec2i_t b,
						    vec2i_t c);

#endif //C_RASTERIZER_H_
