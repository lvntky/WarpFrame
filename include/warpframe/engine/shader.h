#ifndef WARPFRAME_ENGINE_SHADER_H_
#define WARPFRAME_ENGINE_SHADER_H_

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
 public:
  GLuint ID;  // shader id
  Shader(const char* vertexPath, const char* fragmentPath);
  void use();
  void deleteProgram();

 private:
  std::string readFile(const char* filePath);
  GLuint compileShader(GLenum type, const char* source);
  void checkCompileErrors(GLuint shaderID, std::string type);
};

#endif  // WARPFRAME_ENGINE_SHADER_H_
