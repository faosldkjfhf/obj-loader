#include "shader_program.h"
#include <GL/glew.h>
#include <glm/ext.hpp>

ShaderProgram::ShaderProgram() { _id = glCreateProgram(); }
ShaderProgram::~ShaderProgram() { glDeleteProgram(_id); }

void ShaderProgram::Bind() const { glUseProgram(_id); }
void ShaderProgram::Unbind() const { glUseProgram(0); }

void ShaderProgram::AttachShaders(std::vector<Shader> shaders) {
  for (const Shader &shader : shaders) {
    glAttachShader(_id, shader.Location());
  }

  glLinkProgram(_id);
  glUseProgram(_id);

  for (const Shader &shader : shaders) {
    glDeleteShader(shader.Location());
  }
}

void ShaderProgram::SetBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

void ShaderProgram::SetInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void ShaderProgram::SetFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}
void ShaderProgram::SetMat4(const std::string &name, glm::mat4 value) const {
  glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(value));
}
