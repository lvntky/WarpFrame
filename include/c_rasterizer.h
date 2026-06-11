#ifndef C_RASTERIZER_H_
#define C_RASTERIZER_H_

#include <c_renderer.h>
#include <m_type.h>

void c_rasterizer_put_pixel(c_renderer_t *renderer, int x, int y,
			    uint32_t color);
void c_rasterizer_draw_triangle_solid(c_renderer_t *renderer, vec2i_t a,
				      vec2i_t b, vec2i_t c, uint32_t color);

#endif //C_RASTERIZER_H_
