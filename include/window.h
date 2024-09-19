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

  void Close();

  GLFWwindow *GetWindow() const { return _window; }

private:
  int _width;
  int _height;

  GLFWwindow *_window;
};
