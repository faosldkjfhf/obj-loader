#include "shader_program.h"
#include <GL/glew.h>

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
