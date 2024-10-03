#include "window.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

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

  // initialize glew
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cout << "ERROR: " << glewGetErrorString(err) << std::endl;
  }

  // set viewport, update on resize window
  glViewport(0, 0, _width, _height);
  glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

  // mouse input mode
  glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Window::WindowShouldClose() const {
  return glfwWindowShouldClose(_window);
}

void Window::Close() { glfwSetWindowShouldClose(_window, true); }

void Window::SwapBuffers() { glfwSwapBuffers(_window); }
