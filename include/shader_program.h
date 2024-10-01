#pragma once

#include "shader.h"
#include <glm/glm.hpp>
#include <vector>

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram();

  void Bind() const;
  void Unbind() const;

  void AttachShaders(std::vector<Shader> shaders);

  void SetBool(const std::string &name, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetMat4(const std::string &name, glm::mat4 value) const;

private:
  unsigned int _id;
};
