#ifndef C_RASTERIZER_TYPE_H_
#define C_RASTERIZER_TYPE_H_

#include <stdint.h>

typedef struct c_rasterizer_vertex {
	int x;
	int y;
	uint32_t z;
} c_rasterizer_vertex_t;

typedef struct c_rasterizer_triangle {
	c_rasterizer_vertex_t a;
	c_rasterizer_vertex_t b;
	c_rasterizer_vertex_t c;

	uint32_t color;
} c_rasterizer_triangle_t;

#endif //C_RASTERIZER_TYPE_H_
