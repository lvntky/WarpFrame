#include <warpframe/engine/shader.h>
#include <warpframe/logger/logger.h>

std::string Shader::readFile(const char* filePath) {
  std::ifstream file(filePath);
  std::stringstream buffer;
  if (!file) {
    Logger::getLogger()->error("Unable to read file.");
    throw std::runtime_error("File not foud.");
  }
  buffer << file.rdbuf();
  Logger::getLogger()->debug("shader source code: {}", buffer.str());
  return buffer.str();
}

void Shader::checkCompileErrors(GLuint shaderID, std::string type) {
  int success;
  char infoLog[1024];
  if (type == "PROGRAM") {
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shaderID, 1024, nullptr, infoLog);
      Logger::getLogger()->error("Shader program linking error: {}", infoLog);
    }
  } else {
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
      Logger::getLogger()->error("Shader compilation error: {} - shader id: {}",
                                 infoLog, shaderID);
    }
  }
}

GLuint Shader::compileShader(GLenum type, const char* source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  checkCompileErrors(shader,
                     (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));
  return shader;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
  std::string vertexCode, fragmentCode;
  try {
    vertexCode = readFile(vertexPath);
    fragmentCode = readFile(fragmentPath);
  } catch (std::exception& e) {
    Logger::getLogger()->error("Shader file reading error: {}", e.what());
  }
  GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
  GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

  this->ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);

  checkCompileErrors(ID, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() {
  glUseProgram(this->ID);
}

void Shader::deleteProgram() {
  glDeleteProgram(this->ID);
}
