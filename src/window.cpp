#include "window.h"
#include <iostream>

Window::Window() : _width(640), _height(480) { Init(); }

Window::~Window() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

void Window::Init() {
  if (!glfwInit()) {
    std::cout << "Couldn't initialize glfw" << std::endl;
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(_width, _height, "OBJ Loader", nullptr, nullptr);
  if (!_window) {
    std::cout << "Couldn't create window" << std::endl;
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(_window);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cout << "ERROR: " << glewGetErrorString(err) << std::endl;
  }
}

bool Window::WindowShouldClose() const {
  return glfwWindowShouldClose(_window);
}

void Window::PollEvents() const { glfwPollEvents(); }

void Window::SwapBuffers() { glfwSwapBuffers(_window); }
