#include "face.h"

Face::Face(glm::vec3 vertices, glm::vec2 textures, glm::vec3 normals) {
  _vertices = vertices;
  _textures = textures;
  _normals = normals;
}
