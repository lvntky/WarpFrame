#ifndef PLATFORM_SDL_H_
#define PLATFORM_SDL_H_

#include <wf_common.h>

typedef struct wf_platform_t wf_platform_t;

bool wf_platform_init(wf_platform_t** out_platform, int interal_width,
                      int internal_height, int scale);

void wf_platform_shutdown(wf_platform_t* platform);
void wf_platform_poll_input(wf_platform_t* platform, wf_input_t* input);
void wf_platform_clear(wf_platform_t* platform, uint8_t r, uint8_t g,
                       uint8_t b);
void wf_platform_present(wf_platform_t* platform);

float wf_platform_get_delta_time(wf_platform_t* platform);

#endif  //PLATFORM_SDL_H_
