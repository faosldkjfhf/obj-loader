#pragma once

#include "window.h"
#include <memory>

class Engine {
public:
  Engine();
  ~Engine();

  void Loop();
  void Input();
  void Update();
  void Render();

private:
  std::shared_ptr<Window> _window;

  float _deltaTime;
};
