#include "index_buffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, size_t count)
    : _count(count) {
  glGenBuffers(1, &_rendererId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data,
               GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &_rendererId); }

void IndexBuffer::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId); }

void IndexBuffer::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
