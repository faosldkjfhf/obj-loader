#pragma once

#include "camera.h"
#include "face.h"
#include "index_buffer.h"
#include "shader_program.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
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
  std::shared_ptr<Camera> _camera;
  std::shared_ptr<ShaderProgram> _shaderProgram;

  std::vector<Face> _vertices;
  std::vector<unsigned int> _indices;

  std::shared_ptr<VertexArray> _vao;
  std::shared_ptr<VertexBuffer> _vbo;
  std::shared_ptr<IndexBuffer> _ibo;

  glm::mat4 _model;
  glm::mat4 _view;
  glm::mat4 _projection;

  float _deltaTime;
};
