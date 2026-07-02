#ifndef WF_TEXTURE_H_
#define WF_TEXTURE_H_

#include <stdint.h>

typedef struct wf_texture {
	int width;
	int height;
	uint32_t *data;
} wf_texture_t;

#ifdef WF_DEBUG
wf_texture_t *wf_texture_create_checkerboard(void);
#endif

wf_texture_t *load_texture(const char* path);

#endif //WF_TEXTURE_H_
