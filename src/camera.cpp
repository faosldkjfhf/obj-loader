#include "camera.h"
#include <glm/ext.hpp>
#include <iostream>

Camera::Camera() : _speed(5.0f) {
  _position = glm::vec3(0.0f, 0.0f, 7.0f);
  _projection = glm::mat4(1.0f);
  _viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
  _upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera() {}

void Camera::SetProjectionMatrix(float fov, float aspectRatio, float near,
                                 float far) {
  _projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

glm::mat4 Camera::GetViewMatrix() const {
  return glm::lookAt(_position, _position + _viewDirection, _upDirection);
}

void Camera::Input(GLFWwindow *window, float deltaTime) {
  glm::vec3 rightVector =
      glm::normalize(glm::cross(_viewDirection, _upDirection));
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    _position += _viewDirection * _speed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    _position -= _viewDirection * _speed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    _position -= rightVector * _speed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    _position += rightVector * _speed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    _position += _upDirection * _speed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    _position -= _upDirection * _speed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
    _position = glm::vec3(0.0f, 0.0f, 3.0f);
  }

  MouseInput(window);
}

void Camera::Update(float deltaTime) {}

void Camera::MouseInput(GLFWwindow *window) {
  auto mouseCallback = [](GLFWwindow *window, double xpos, double ypos) {
    auto me = (Camera *)glfwGetWindowUserPointer(window);
    me->MouseCallback(window, xpos, ypos);
  };

  glfwSetWindowUserPointer(window, this);
  glfwSetCursorPosCallback(window, mouseCallback);
}

void Camera::MouseCallback(GLFWwindow *window, double xpos, double ypos) {}
