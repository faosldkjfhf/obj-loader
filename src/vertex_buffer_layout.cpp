#include "vertex_buffer_layout.h"

VertexBufferLayout::VertexBufferLayout() { _stride = 0; }

template <> void VertexBufferLayout::Push<float>(unsigned int count) {
  _elements.push_back(VertexBufferElement{GL_FLOAT, count, GL_FALSE});
  _stride += VertexBufferElement::Size(GL_FLOAT) * count;
}

template <> void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
  _elements.push_back(VertexBufferElement{GL_UNSIGNED_INT, count, GL_FALSE});
  _stride += VertexBufferElement::Size(GL_UNSIGNED_INT) * count;
}

template <> void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
  _elements.push_back(VertexBufferElement{GL_UNSIGNED_BYTE, count, GL_TRUE});
  _stride += VertexBufferElement::Size(GL_UNSIGNED_BYTE) * count;
}
