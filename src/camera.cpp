#include "camera.h"

Camera::Camera() {
  _position = glm::vec3(0.0f, 0.0f, -5.0f);
  _viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
  _upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
  _projection = glm::mat4(1.0f);
}

Camera::~Camera() {}

void Camera::Input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W)) {
    _position.z -= 0.5f;
  } else if (glfwGetKey(window, GLFW_KEY_S)) {
    _position.z += 0.5f;
  } else if (glfwGetKey(window, GLFW_KEY_A)) {
    _position.x -= 0.5f;
  } else if (glfwGetKey(window, GLFW_KEY_D)) {
    _position.x += 0.5f;
  }
}

void Camera::Update() {}
