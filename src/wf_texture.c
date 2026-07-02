#include <wf_texture.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#ifdef WF_DEBUG
// 64x64 checkerboard texture generator

wf_texture_t *wf_texture_create_checkerboard(void)
{
	const int width = 64;
	const int height = 64;

	wf_texture_t *texture = malloc(sizeof(wf_texture_t));
	texture->width = width;
	texture->height = height;
	texture->data = malloc(width * height * sizeof(uint32_t));

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// 8x8 checker cells
			int cx = x / 8;
			int cy = y / 8;

			bool white = ((cx + cy) % 2) == 0;

			uint32_t color = white ? 0xFFFFFFFF : 0xFF000000;

			texture->data[y * width + x] = color;
		}
	}

	return texture;
}

#endif

wf_texture_t *load_texture(const char *path)
{
	wf_texture_t *tex = NULL;
	return tex;
}
