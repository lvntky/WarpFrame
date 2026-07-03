#include <wf_texture.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include <stb_image.h>

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
	int width, height, channels;
	unsigned char *data = stbi_load(path, &width, &height, &channels, 4);
	if (!data)
		return NULL;

	wf_texture_t *tex = malloc(sizeof(wf_texture_t));
	if (!tex) {
		stbi_image_free(data);
		return NULL;
	}

	tex->width = width;
	tex->height = height;
	tex->data = malloc((size_t)width * height * sizeof(uint32_t));
	if (!tex->data) {
		free(tex);
		stbi_image_free(data);
		return NULL;
	}

	for (int i = 0; i < width * height; i++) {
		unsigned char r = data[i * 4 + 0];
		unsigned char g = data[i * 4 + 1];
		unsigned char b = data[i * 4 + 2];
		unsigned char a = data[i * 4 + 3];
		tex->data[i] = ((uint32_t)a << 24) | ((uint32_t)r << 16) |
			       ((uint32_t)g << 8) | (uint32_t)b;
	}

	stbi_image_free(data);
	return tex;
}
