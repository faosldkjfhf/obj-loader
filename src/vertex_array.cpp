#include "vertex_array.h"
#include <GL/glew.h>

VertexArray::VertexArray() {
  glGenVertexArrays(1, &_id);
  glBindVertexArray(_id);
  Bind();
}

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &_id); }

void VertexArray::AddBuffer(const VertexBuffer &vb,
                            const VertexBufferLayout &layout) {
  const auto &elements = layout.Elements();
  unsigned int offset = 0;

  // Vertices
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Face),
                        (void *)offsetof(Face, _vertices));
}

void VertexArray::Bind() const { glBindVertexArray(_id); }

void VertexArray::Unbind() const { glBindVertexArray(0); }
