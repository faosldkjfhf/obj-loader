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

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float),
               _vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
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
  glBindVertexArray(_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  _window->SwapBuffers();
}

void Engine::Update() {}
