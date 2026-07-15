#ifndef PLATFORM_SDL_H_
#define PLATFORM_SDL_H_

#include <wf_common.h>
#include <SDL2/SDL.h>

typedef struct wf_platform_t wf_platform_t;

#define WF_CONTROL_PANEL_WIDTH 340

SDL_Rect wf_platform_get_render_rect(wf_platform_t *platform);
SDL_Rect wf_platform_get_panel_rect(wf_platform_t *platform);

bool wf_platform_init(wf_platform_t **out_platform, int interal_width,
		      int internal_height, int scale);

void wf_platform_shutdown(wf_platform_t *platform);
void wf_platform_poll_input(wf_input_t *input);
void wf_platform_clear(wf_platform_t *platform, uint8_t r, uint8_t g,
		       uint8_t b);
void wf_platform_present(wf_platform_t *platform, uint32_t *frame_data);

float wf_platform_get_delta_time(wf_platform_t *platform);

void wf_platform_present_framebuffer(wf_platform_t *platform,
				     const uint32_t *framebuffer);
void wf_platform_begin_ui(wf_platform_t *platform);
void wf_platform_end_ui(wf_platform_t *platform);
SDL_Renderer *wf_platform_get_renderer(wf_platform_t *platform);
int wf_platform_get_window_width(wf_platform_t *platform);
int wf_platform_get_window_height(wf_platform_t *platform);

#endif //PLATFORM_SDL_H_
