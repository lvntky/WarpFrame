#ifndef WF_COMMON_H_
#define WF_COMMON_H_

#include <stdbool.h>
#include <stdint.h>

#define WF_INTERNAL_WIDTH 320
#define WF_INTERNAL_HEIGHT 240
#define WF_WINDOW_SCALE 3

#define WF_WINDOW_WIDTH (WF_INTERNAL_WIDTH * WF_WINDOW_SCALE)
#define WF_WINDOW_HEIGHT (WF_INTERNAL_HEIGHT * WF_WINDOW_SCALE)

typedef struct wf_input {
  bool quit;

  bool key_up;
  bool key_down;
  bool key_left;
  bool key_right;

  bool key_escape;
} wf_input_t;

#endif  // WF_COMMON_H_
