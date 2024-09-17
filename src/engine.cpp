#include "engine.h"
#include <iostream>

Engine::Engine() : _window(std::make_shared<Window>()) {}

Engine::~Engine() {}

void Engine::Loop() {
  while (!_window->WindowShouldClose()) {
    Input();
    Update();
    Render();
  }

  std::cout << "Exiting app" << std::endl;
}

void Engine::Input() { _window->PollEvents(); }

void Engine::Render() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Render loop goes here

  _window->SwapBuffers();
}

void Engine::Update() {}
