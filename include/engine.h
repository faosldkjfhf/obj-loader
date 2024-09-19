#pragma once

#include "shader_program.h"
#include "window.h"
#include <memory>
#include <vector>

class Engine {
public:
  Engine();
  ~Engine();

  void InitializeBuffers();

  void Loop();
  void Input();
  void Update();
  void Render();

private:
  std::shared_ptr<Window> _window;
  std::shared_ptr<ShaderProgram> _shaderProgram;

  std::vector<float> _vertices;
  std::vector<unsigned int> _indices;
  unsigned int _vbo;
  unsigned int _vao;

  float _deltaTime;
};
