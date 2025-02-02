#include <warpframe/logger/logger.h>
#include <warpframe/window/window.h>

Window::Window(size_t width, size_t height, const char* title) {
  if (!glfwInit()) {
    Logger::getLogger()->error("Unable to initialize GLFW");
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!this->window) {
    Logger::getLogger()->error("Failed to create GLFW window");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(this->window);
  initGlad();
  if (!validateOpenGL()) {
    return;
  }

  Logger::getLogger()->info(
      "OpenGL version supported: {}",
      reinterpret_cast<const char*>(glGetString(GL_VERSION)));

  Logger::getLogger()->info(
      "Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
}

Window::~Window() {
  if (this->window) {
    Logger::getLogger()->info("GLFW Window has been terminated.");
    glfwDestroyWindow(this->window);
  }
  glfwTerminate();
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() {
  //  Logger::getLogger()->info("Swapping buffers on GLFW Window.");
  glfwSwapBuffers(this->window);
}

void Window::pollEvents() {
  //Logger::getLogger()->info("Polling events on GLFW window.");
  glfwPollEvents();
}

void Window::clear() {
  glClearColor(0.125f, 0.125f, 0.439f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::initGlad() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::getLogger()->error("Failed to load GLAD");
  }
}

bool Window::validateOpenGL() {
  const GLubyte* version = glGetString(GL_VERSION);

  if (!version) {
    Logger::getLogger()->error("Failed to retrieve OpenGL version.");
    return false;
  }
  return true;
}

void Window::processInput() {
  if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(this->window, true);
  }
}
