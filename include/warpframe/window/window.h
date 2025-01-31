#ifndef WARPFRAME_WINDOW_H_
#define WARPFRAME_WINDOW_H_

#include <GLFW/glfw3.h>
#include <cstddef>

#include <glad/glad.h>

class Window {
 private:
  GLFWwindow* window = nullptr;

 public:
  Window(size_t width, size_t height, const char* title);
  ~Window();

  bool shouldClose() const;
  void swapBuffers();
  void pollEvents();
  void clear();
  GLFWwindow* getGLFWwindow() const;
};

#endif  // WARPFRAME_WINDOW_H_
