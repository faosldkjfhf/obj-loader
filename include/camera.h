#pragma once

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
  Camera();
  ~Camera();

  void Input(GLFWwindow *window);
  void Update();

private:
  glm::vec3 _viewDirection;
  glm::vec3 _upDirection;
  glm::vec3 _position;
  glm::mat4 _projection;
};
