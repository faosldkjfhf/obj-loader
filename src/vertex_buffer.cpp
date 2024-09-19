#include "vertex_buffer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int count) {
  glGenBuffers(1, &_id);
  Bind();
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &_id); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, _id); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
