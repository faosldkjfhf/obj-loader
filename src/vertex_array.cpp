#include "vertex_array.h"
#include "face.h"
#include <GL/glew.h>

VertexArray::VertexArray() {
  glGenVertexArrays(1, &_id);
  glBindVertexArray(_id);
}

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &_id); }

void VertexArray::Initialize() {
  // Vertices
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Face),
                        (void *)offsetof(Face, _vertices));

  // Textures
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Face),
                        (void *)offsetof(Face, _textures));

  // Normals
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Face),
                        (void *)offsetof(Face, _normals));
}

void VertexArray::Bind() const { glBindVertexArray(_id); }

void VertexArray::Unbind() const { glBindVertexArray(0); }
