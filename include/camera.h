#pragma once

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// TODO: Fix moving around

class Camera {
public:
  Camera();
  ~Camera();

  void SetProjectionMatrix(float fov, float aspectRatio, float near, float far);
  glm::mat4 GetProjectionMatrix() const { return _projection; }
  glm::mat4 GetViewMatrix() const;
  glm::vec3 GetPosition() const { return _position; }

  void Input(GLFWwindow *window, float deltaTime);
  void Update(float deltaTime);

  void MouseInput(GLFWwindow *window);
  void MouseCallback(GLFWwindow *window, double xpos, double ypos);

private:
  glm::vec3 _viewDirection;
  glm::vec3 _upDirection;

  glm::vec3 _position;
  glm::mat4 _projection;

  float _speed;
  float _lastXPos;
  float _lastYPos;
};
