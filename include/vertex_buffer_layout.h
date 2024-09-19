#pragma once

#include <GL/glew.h>
#include <vector>

struct VertexBufferElement {
  unsigned int type;
  unsigned int count;
  bool normalized;

  static unsigned int Size(unsigned int type) {
    switch (type) {
    case GL_FLOAT:
      return 4;
    case GL_UNSIGNED_INT:
      return 4;
    case GL_UNSIGNED_BYTE:
      return 1;
    }

    return 0;
  }
};

class VertexBufferLayout {
public:
  VertexBufferLayout();

  template <typename T> void Push(unsigned int count);

  inline unsigned int Stride() const { return _stride; }

  inline std::vector<VertexBufferElement> Elements() const & {
    return _elements;
  }

private:
  std::vector<VertexBufferElement> _elements;
  unsigned int _stride;
};
