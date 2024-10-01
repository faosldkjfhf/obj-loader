#include "engine.h"
#include "obj_loader.h"
#include "shader.h"
#include <glm/ext.hpp>
#include <iostream>

Engine::Engine()
    : _window(std::make_shared<Window>()),
      _shaderProgram(std::make_shared<ShaderProgram>()),
      _camera(std::make_shared<Camera>()) {
  // Create vertex and fragment shaders
  std::vector<Shader> shaders;
  shaders.push_back(Shader(GL_VERTEX_SHADER, "./shaders/vert.glsl"));
  shaders.push_back(Shader(GL_FRAGMENT_SHADER, "./shaders/frag.glsl"));
  _shaderProgram->AttachShaders(shaders);

  // Initialize buffers
  InitializeBuffers();
}

Engine::~Engine() {}

void Engine::Loop() {
  while (!_window->WindowShouldClose()) {
    Input();
    Update();
    Render();
  }

  std::cout << "Exiting app" << std::endl;
}

void Engine::InitializeBuffers() {
  ObjLoader::LoadObj(_vertices, _indices, "./models/cube.obj");

  _vao = std::make_shared<VertexArray>();
  _vbo = std::make_shared<VertexBuffer>(_vertices.data(), _vertices.size(),
                                        sizeof(Face));
  _ibo = std::make_shared<IndexBuffer>(_indices.data(), _indices.size());

  VertexBufferLayout layout;
  layout.Push<Face>(3);
  // layout.Push<Face>(2);
  // layout.Push<Face>(3);

  _vao->AddBuffer(*_vbo, layout);

  _projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

  _model = glm::mat4(1.0f);
  _model =
      glm::rotate(_model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

  _view = glm::mat4(1.0f);
  _view = glm::translate(_view, glm::vec3(0.0f, 0.0f, -5.0f));
}

void Engine::Input() {
  GLFWwindow *window = _window->GetWindow();
  glfwPollEvents();
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    _window->Close();
  }

  _camera->Input(window);
}

void Engine::Render() {
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Render loop goes here
  _shaderProgram->Bind();
  _vao->Bind();
  glDrawElements(GL_TRIANGLES, _ibo->Count(), GL_UNSIGNED_INT, nullptr);

  // Swap buffers
  _window->SwapBuffers();
}

void Engine::Update() {
  _shaderProgram->SetMat4("model", _model);
  _shaderProgram->SetMat4("projection", _projection);
  _shaderProgram->SetMat4("view", _view);
}
