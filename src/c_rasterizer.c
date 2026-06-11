#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <c_rasterizer.h>
#include <wf_common.h>
#include <m_type.h>
#include <m_util.h>

static int edge_function(vec2i_t a, vec2i_t b, vec2i_t p)
{
	vec2i_t ab = { (b.y - a.y), (b.x - a.x) };
	vec2i_t ap = { (p.y - a.y), (p.x - a.x) };
	return m_det2i(ab, ap) >= 0;
}

static bool is_point_inside_triange(vec2i_t a, vec2i_t b, vec2i_t c, vec2i_t p)
{
	bool w0 = edge_function(a, b, p);
	bool w1 = edge_function(b, c, p);
	bool w2 = edge_function(c, a, p);
	return (w0 && w1 && w2);
}

void c_rasterizer_put_pixel(c_renderer_t *renderer, int x, int y,
			    uint32_t color)
{
	if (x < 0 || x >= WF_INTERNAL_WIDTH) {
		return;
	}

	if (y < 0 || y >= WF_INTERNAL_HEIGHT) {
		return;
	}

	renderer->color_buffer[y * WF_INTERNAL_WIDTH + x] = color;
}

void c_rasterizer_draw_triangle_solid(c_renderer_t *renderer, vec2i_t a,
				      vec2i_t b, vec2i_t c, uint32_t color)
{
	for (int i = 0; i < renderer->data_len; i++) {
		int local_x = i % WF_INTERNAL_WIDTH;
		int local_y = i / WF_INTERNAL_WIDTH;

		vec2i_t p = { local_x, local_y };

		if (is_point_inside_triange(a, b, c, p)) {
			c_rasterizer_put_pixel(renderer, local_x, local_y,
					       color);
		}
	}
}
