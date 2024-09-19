#include "shader.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>

Shader::Shader(unsigned int type, const std::string &file)
    : _file(file), _type(type) {
  _id = CompileShader();
}

void Shader::Bind(unsigned int program) const { glAttachShader(program, _id); }
void Shader::Unbind(unsigned int program) const {
  glDetachShader(program, _id);
}

unsigned int Shader::CompileShader() {
  std::string source = LoadAsString();
  unsigned int id = glCreateShader(_type);
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  char infoLog[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (!result) {
    glGetShaderInfoLog(_id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    glDeleteShader(_id);
    return 0;
  }

  std::cout << _file << " compiled successfully" << std::endl;
  return id;
}

std::string Shader::LoadAsString() const {
  std::string result = "";
  std::ifstream input(_file);
  if (!input.is_open()) {
    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
              << "Couldn't read input file " << _file << std::endl;
    return "";
  }

  std::string line = "";
  while (std::getline(input, line)) {
    result += line + "\n";
  }

  input.close();
  return result;
}
