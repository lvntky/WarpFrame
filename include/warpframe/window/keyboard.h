#ifndef WARPFRAME_WINDOW_KEYBOARD_H_
#define WARPFRAME_WINDOW_KEYBOARD_H_

#include <GLFW/glfw3.h>
#include <array>
#include <functional>
#include <unordered_map>

#define WARPFRAME_WINDOW_KEYBOARD_MAX_KEY (GLFW_KEY_LAST + 1)

class Keyboard {
 public:
  enum class KeyState { RELEASED, PRESSED, HELD, REPEAT };
};

#endif  // WARPFRAME_WINDOW_KEYBOARD_H_