#pragma once

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
  Window();
  ~Window();

  void Init();
  void SwapBuffers();
  bool WindowShouldClose() const;
  void PollEvents() const;

private:
  int _width;
  int _height;

  GLFWwindow *_window;
};
