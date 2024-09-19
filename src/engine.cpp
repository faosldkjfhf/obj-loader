#include "engine.h"
#include "shader.h"
#include <iostream>

Engine::Engine()
    : _window(std::make_shared<Window>()),
      _shaderProgram(std::make_shared<ShaderProgram>()) {
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
  _vertices = {
      -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
  };
  _indices = {0, 1, 2};

  _vao = std::make_shared<VertexArray>();
  _vbo = std::make_shared<VertexBuffer>(_vertices.data(), _vertices.size());
  _ibo = std::make_shared<IndexBuffer>(_indices.data(), _indices.size());

  VertexBufferLayout layout;
  layout.Push<float>(3);

  _vao->AddBuffer(*_vbo, layout);
}

void Engine::Input() {
  GLFWwindow *window = _window->GetWindow();
  glfwPollEvents();
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    _window->Close();
  }
}

void Engine::Render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Render loop goes here
  _shaderProgram->Bind();
  _vao->Bind();
  glDrawElements(GL_TRIANGLES, _ibo->Count(), GL_UNSIGNED_INT, nullptr);

  _window->SwapBuffers();
}

void Engine::Update() {}
