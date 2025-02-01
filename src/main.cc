#include <warpframe/engine/shader.h>
#include <warpframe/logger/logger.h>
#include <warpframe/util/constant.h>
#include <warpframe/window/window.h>

#include <iostream>

static const float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                 0.0f,  0.0f,  0.5f, 0.0f};

static const char* vertexPath = "./assets/shaders/vertex.glsl";
static const char* fragmentPath = "./assets/shaders/fragment.glsl";

int main() {
  Logger::init();
  Logger::getLogger()->info("WarpFrame initialized.");

  Window window(DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT, TITLE);

  Shader shader(vertexPath, fragmentPath);

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // basic render loop
  while (!window.shouldClose()) {
    window.clear();

    window.processInput();

    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
