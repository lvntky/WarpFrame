#ifndef C_RASTERIZER_H_
#define C_RASTERIZER_H_

#include <c_renderer.h>
#include <m_type.h>
#include <c_rasterizer_type.h>

typedef struct bounding_box_t bounding_box_t;

void c_rasterizer_put_pixel(c_renderer_t *renderer, int x, int y,
			    uint32_t color);
void c_rasterizer_draw_triangle_solid(c_renderer_t *renderer,
				      c_rasterizer_triangle_t triangle);

bounding_box_t
c_rasterizer_triange_calculate_bounding_box(c_rasterizer_triangle_t triangle);

void c_rasterizer_draw_triangle_bounding_box_points(c_renderer_t *renderer,
						    c_rasterizer_triangle_t triangle);

#endif //C_RASTERIZER_H_
