#include "vertex_buffer_layout.h"

VertexBufferLayout::VertexBufferLayout() { _stride = 0; }

template <> void VertexBufferLayout::Push<float>(unsigned int count) {
  _elements.push_back(VertexBufferElement{SizeType::FLOAT, count, GL_FALSE});
  _stride += VertexBufferElement::Size(SizeType::FLOAT) * count;
}

template <> void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
  _elements.push_back(
      VertexBufferElement{SizeType::UNSIGNED_INT, count, GL_FALSE});
  _stride += VertexBufferElement::Size(SizeType::UNSIGNED_INT) * count;
}

template <> void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
  _elements.push_back(
      VertexBufferElement{SizeType::UNSIGNED_BYTE, count, GL_TRUE});
  _stride += VertexBufferElement::Size(SizeType::UNSIGNED_BYTE) * count;
}

template <> void VertexBufferLayout::Push<Face>(unsigned int count) {
  _elements.push_back(VertexBufferElement{SizeType::FLOAT, count, GL_TRUE});
  _stride += VertexBufferElement::Size(SizeType::FACE);
}
