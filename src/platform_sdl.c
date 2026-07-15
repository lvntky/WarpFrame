#include <platform_sdl.h>

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

struct wf_platform_t {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *framebuffer_texture;

	int internal_width;
	int internal_height;
	int window_width;
	int window_height;

	uint64_t last_counter;
	float delta_time;
};

bool wf_platform_init(wf_platform_t **out_platform, int interal_width,
		      int internal_height, int scale)
{
#ifdef WF_DEBUG
	SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
#endif
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
		return false;
	}

	wf_platform_t *platform = calloc(1, sizeof(wf_platform_t));
	if (!platform) {
		SDL_Quit();
		return false;
	}

	platform->internal_width = interal_width;
	platform->internal_height = internal_height;
	platform->window_width = interal_width * scale + WF_CONTROL_PANEL_WIDTH;
	platform->window_height = internal_height * scale;

	platform->window =
		SDL_CreateWindow("WarpFrame", SDL_WINDOWPOS_CENTERED,
				 SDL_WINDOWPOS_CENTERED, platform->window_width,
				 platform->window_height, SDL_WINDOW_SHOWN);

	if (!platform->window) {
		fprintf(stderr, "SDL_CreateWindow failed: %s\n",
			SDL_GetError());
		free(platform);
		SDL_Quit();
		return false;
	}

	platform->renderer = SDL_CreateRenderer(
		platform->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!platform->renderer) {
		fprintf(stderr, "SDL_CreateRenderer failed: %s\n",
			SDL_GetError());
		SDL_DestroyWindow(platform->window);
		free(platform);
		SDL_Quit();
		return false;
	}

	platform->framebuffer_texture = SDL_CreateTexture(
		platform->renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, platform->internal_width,
		platform->internal_height);

	if (!platform->framebuffer_texture) {
		fprintf(stderr, "SDL_CreateTexture failed: %s\n",
			SDL_GetError());
		SDL_DestroyRenderer(platform->renderer);
		SDL_DestroyWindow(platform->window);
		free(platform);
		SDL_Quit();
		return false;
	}

	SDL_RenderSetLogicalSize(platform->renderer, 0, 0);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	platform->last_counter = SDL_GetPerformanceCounter();
	platform->delta_time = 0.0f;

	*out_platform = platform;

	return true;
}

void wf_platform_shutdown(wf_platform_t *platform)
{
	if (!platform) {
		return;
	}

	if (platform->framebuffer_texture) {
		SDL_DestroyTexture(platform->framebuffer_texture);
	}

	if (platform->renderer) {
		SDL_DestroyRenderer(platform->renderer);
	}

	if (platform->window) {
		SDL_DestroyWindow(platform->window);
	}

	free(platform);
	SDL_Quit();
}

void wf_platform_clear(wf_platform_t *platform, uint8_t r, uint8_t g, uint8_t b)
{
	SDL_SetRenderDrawColor(platform->renderer, r, g, b, 255);
	SDL_RenderClear(platform->renderer);
}

void wf_platform_present(wf_platform_t *platform, uint32_t *frame_data)
{
	wf_platform_present_framebuffer(platform, frame_data);
	SDL_RenderPresent(platform->renderer);
}

float wf_platform_get_delta_time(wf_platform_t *platform)
{
	uint64_t now = SDL_GetPerformanceCounter();
	uint64_t freq = SDL_GetPerformanceFrequency();

	platform->delta_time =
		(float)(now - platform->last_counter) / (float)freq;
	platform->last_counter = now;

	return platform->delta_time;
}

SDL_Rect wf_platform_get_render_rect(wf_platform_t *platform)
{
	SDL_Rect r;
	r.x = WF_CONTROL_PANEL_WIDTH;
	r.y = 0;
	r.w = platform->window_width - WF_CONTROL_PANEL_WIDTH;
	r.h = platform->window_height;
	return r;
}

SDL_Rect wf_platform_get_panel_rect(wf_platform_t *platform)
{
	SDL_Rect r = { 0, 0, WF_CONTROL_PANEL_WIDTH, platform->window_height };
	return r;
}

void wf_platform_present_framebuffer(wf_platform_t *platform,
				     const uint32_t *framebuffer)
{
	SDL_UpdateTexture(platform->framebuffer_texture, NULL, framebuffer,
			  platform->internal_width * sizeof(uint32_t));
	SDL_Rect dst = wf_platform_get_render_rect(platform);
	SDL_RenderCopy(platform->renderer, platform->framebuffer_texture, NULL,
		       &dst);
}

void wf_platform_begin_ui(wf_platform_t *platform)
{
	(void)platform;
}

void wf_platform_end_ui(wf_platform_t *platform)
{
	(void)platform;
}

SDL_Renderer *wf_platform_get_renderer(wf_platform_t *platform)
{
	return platform->renderer;
}

int wf_platform_get_window_width(wf_platform_t *platform)
{
	return platform->window_width;
}

int wf_platform_get_window_height(wf_platform_t *platform)
{
	return platform->window_height;
}
