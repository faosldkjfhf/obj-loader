#include "engine.h"
#include "obj_loader.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <iostream>

Engine::Engine()
    : _window(std::make_shared<Window>()),
      _shaderProgram(std::make_shared<ShaderProgram>()),
      _camera(std::make_shared<Camera>()), _wireframeMode(false) {

  // Create vertex and fragment shaders
  std::vector<Shader> shaders;
  shaders.push_back(Shader(GL_VERTEX_SHADER, "./shaders/vert.glsl"));
  shaders.push_back(Shader(GL_FRAGMENT_SHADER, "./shaders/frag.glsl"));
  _shaderProgram->AttachShaders(shaders);

  // Initialize camera and matrices
  _camera->SetProjectionMatrix(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
  _model = glm::mat4(1.0f);
  _view = glm::mat4(1.0f);

  // Initialize buffers
  InitializeBuffers();
}

Engine::~Engine() {}

void Engine::Loop() {
  _currentFrame = glfwGetTime();
  float lastFrame = _currentFrame;
  float runningTime = 0.0f;
  unsigned int frames = 0;
  while (!_window->WindowShouldClose()) {
    Input();
    Update();
    Render();

    lastFrame = _currentFrame;
    _currentFrame = glfwGetTime();
    _deltaTime = _currentFrame - lastFrame;
    runningTime += _deltaTime;
    frames++;

    // std::cout << "deltaTime: " << _deltaTime << std::endl;

    if (runningTime - 1.0f >= 0.001f) {
      // std::cout << "FPS: " << frames << std::endl;
      frames = 0;
      runningTime = 0.0f;
    }
  }

  std::cout << "Exiting app..." << std::endl;
}

void Engine::InitializeBuffers() {
  ObjLoader::LoadObj(_vertices, _indices, "./models/cube.obj");

  _vao = std::make_shared<VertexArray>();
  _vbo = std::make_shared<VertexBuffer>(_vertices.data(), _vertices.size(),
                                        sizeof(Face));
  _ibo = std::make_shared<IndexBuffer>(_indices.data(), _indices.size());

  // Initialize vertex array
  _vao->Initialize();

  // Setup model view projection matrices
  _projection = _camera->GetProjectionMatrix();
  _view = _camera->GetViewMatrix();
}

void Engine::tabKeyCallback(GLFWwindow *window, int key, int scancode,
                            int action, int mods) {
  if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
    _wireframeMode = !_wireframeMode;
  }
}

void Engine::Input() {
  GLFWwindow *window = _window->GetWindow();
  glfwPollEvents();
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    _window->Close();
  }

  // auto keyCallback = [](GLFWwindow *window, int key, int scancode, int
  // action,
  //                       int mods) {
  //   auto me = (Engine *)glfwGetWindowUserPointer(window);
  //   me->tabKeyCallback(window, key, scancode, action, mods);
  // };
  //
  // glfwSetWindowUserPointer(window, this);
  // glfwSetKeyCallback(window, keyCallback);

  _camera->Input(window, _deltaTime);
}

void Engine::Render() {
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Wireframe mode
  if (_wireframeMode) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  // Render loop goes here
  _shaderProgram->Bind();
  _vao->Bind();
  glDrawElements(GL_TRIANGLES, _ibo->Count(), GL_UNSIGNED_INT, nullptr);

  // Swap buffers
  _window->SwapBuffers();
}

void Engine::Update() {
  // Update camera, view, and projection matrices
  _camera->Update(_deltaTime);
  _view = _camera->GetViewMatrix();
  _projection = _camera->GetProjectionMatrix();

  _shaderProgram->SetMat4("model", _model);
  _shaderProgram->SetMat4("projection", _projection);
  _shaderProgram->SetMat4("view", _view);
}
