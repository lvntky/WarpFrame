#ifndef C_RENDERER_H_
#define C_RENDERER_H_

#include <stdint.h>

typedef struct c_renderer {
	uint32_t *framebuffer;
	uint32_t *color_buffer;
	uint32_t *depth_buffer;

} c_renderer_t;

int c_renderer_init(c_renderer_t **renderer);
void c_renderer_shutdown(c_renderer_t *renderer);

#endif //C_RENDERER_H_
