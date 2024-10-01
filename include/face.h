#pragma once

#include <glm/glm.hpp>
#include <ostream>

struct Face {
  Face(glm::vec3 vertices, glm::vec2 textures, glm::vec3 normals);
  ~Face() {}

  bool operator==(const Face &f) {
    return _vertices == f._vertices && _textures == f._textures &&
           _normals == f._normals;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Face &f) {
    stream << "Vertices: " << f._vertices.x << " " << f._vertices.y << " "
           << f._vertices.z << std::endl;
    stream << "Textures: " << f._textures.x << " " << f._textures.y
           << std::endl;
    stream << "Normals: " << f._normals.x << " " << f._normals.y << " "
           << f._normals.z << std::endl;
    return stream;
  }

  glm::vec3 _vertices;
  glm::vec2 _textures;
  glm::vec3 _normals;
};
