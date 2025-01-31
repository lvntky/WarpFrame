#include <warpframe/logger/logger.h>
#include <warpframe/window/window.h>

Window::Window(size_t width, size_t height, const char* title) {
  if (!glfwInit()) {
    Logger::getLogger()->error("Unable to initialize GLFW");
    return;
  }

  this->window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!this->window) {
    Logger::getLogger()->error("Failed to create GLFW window");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(this->window);
  initGlad();

  glViewport(0, 0, width, height);
}

Window::~Window() {
  if (this->window) {
    // Logger::getLogger->info("GLFW Window has been terminated.");
    glfwDestroyWindow(this->window);
  }
  glfwTerminate();
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() {
  // Logger::getLogger->info("Swapping buffers on GLFW Window.");
  glfwSwapBuffers(this->window);
}

void Window::pollEvents() {
  // Logger::getLogger->info("Polling events on GLFW window.");
  glfwPollEvents();
}

void Window::clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::initGlad() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::getLogger()->error("Failed to load GLAD");
  }
}
