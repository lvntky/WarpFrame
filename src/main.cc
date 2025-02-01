#include <warpframe/logger/logger.h>
#include <warpframe/util/constant.h>
#include <warpframe/window/window.h>

#include <iostream>

static const float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                 0.0f,  0.0f,  0.5f, 0.0f};

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "    out vec4 FragColor;\n"
    "    void main() {\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main() {
  Logger::init();
  Logger::getLogger()->info("WarpFrame initialized.");

  Window window(DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT, TITLE);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // vertex shader for debug and test
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

  if (!success) {
    Logger::getLogger()->error("Unable to compile vertex shader: {}", infoLog);
  } else {
    Logger::getLogger()->info("Vertex shader compiled successfully.");
  }

  // fragment shader for debug and test
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    Logger::getLogger()->error("Unable to compile fragment sahder.");
  } else {
    Logger::getLogger()->info("Fragment shader compiled successfully");
  }

  // shader program itself
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {

    Logger::getLogger()->error("Unable to link shader program.");
  } else {
    Logger::getLogger()->info("Shader program linked successfully.");
  }

  glUseProgram(shaderProgram);

  // basic render loop
  while (!window.shouldClose()) {
    window.clear();

    window.processInput();

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
