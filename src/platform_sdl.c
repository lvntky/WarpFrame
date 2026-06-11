#include <platform_sdl.h>

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

struct wf_platform_t {
	SDL_Window *window;
	SDL_Renderer *renderer;

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
	platform->window_width = interal_width * scale;
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

	SDL_RenderSetLogicalSize(platform->renderer, platform->internal_width,
				 platform->internal_height);

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

void wf_platform_poll_input(wf_platform_t *platform, wf_input_t *input)
{
	input->key_up = false;
	input->key_down = false;
	input->key_left = false;
	input->key_right = false;
	input->key_escape = false;

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			input->quit = true;
		}

		if (event.type == SDL_KEYDOWN) {
			SDL_KeyCode key = event.key.keysym.sym;
			if (key == SDLK_ESCAPE) {
				input->quit = true;
				input->key_escape = true;
			}
		}

		const uint8_t *keyboard = SDL_GetKeyboardState(NULL);

		input->key_up = keyboard[SDL_SCANCODE_W] ||
				keyboard[SDL_SCANCODE_UP];
		input->key_down = keyboard[SDL_SCANCODE_S] ||
				  keyboard[SDL_SCANCODE_DOWN];
		input->key_left = keyboard[SDL_SCANCODE_A] ||
				  keyboard[SDL_SCANCODE_LEFT];
		input->key_right = keyboard[SDL_SCANCODE_D] ||
				   keyboard[SDL_SCANCODE_RIGHT];
	}
}

void wf_platform_present(wf_platform_t* platform) {
	SDL_RenderPresent(platform->renderer);
}

float wf_platform_get_delta_time(wf_platform_t* platform) {
	uint64_t now = SDL_GetPerformanceCounter();
	uint64_t freq = SDL_GetPerformanceFrequency();

	platform->delta_time = (float)(now - platform->last_counter) / (float)freq;
	platform->last_counter = now;

	return platform->delta_time;
}
