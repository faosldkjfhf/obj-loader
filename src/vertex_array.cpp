#include "vertex_array.h"
#include <GL/glew.h>
#include <iostream>

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

  for (unsigned int i = 0; i < elements.size(); i++) {
    const auto &element = elements[i];

    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type, element.normalized,
                          layout.Stride(), (const void *)offset);
    offset += element.count * VertexBufferElement::Size(element.type);
  }
}

void VertexArray::Bind() const { glBindVertexArray(_id); }

void VertexArray::Unbind() const { glBindVertexArray(0); }
