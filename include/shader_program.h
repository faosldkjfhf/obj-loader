#pragma once

#include "shader.h"
#include <vector>

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram();

  void Bind() const;
  void Unbind() const;

  void AttachShaders(std::vector<Shader> shaders);

private:
  unsigned int _id;
};
