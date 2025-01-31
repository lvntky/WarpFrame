#ifndef WARPFRAME_WINDOW_WINDOW_H_
#define WARPFRAME_WINDOW_WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <warpframe/window/keyboard.h>

class Window {
 private:
  GLFWwindow* window = nullptr;
  std::unique_ptr<Keyboard> keyboard;

  void initGlad();
  bool validateOpenGL();

 public:
  Window(size_t width, size_t height, const char* title);
  ~Window();

  bool shouldClose() const;
  void swapBuffers();
  void pollEvents();
  void clear();
  GLFWwindow* getGLFWwindow() const;
};

#endif  // WARPFRAME_WINDOW_WINDOW_H_
