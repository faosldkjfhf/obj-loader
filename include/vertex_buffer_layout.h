#pragma once

#include "face.h"
#include <GL/glew.h>
#include <vector>

enum SizeType {
  FLOAT,
  UNSIGNED_INT,
  UNSIGNED_BYTE,
  FACE,
};

struct VertexBufferElement {
  SizeType type;
  unsigned int count;
  bool normalized;

  static unsigned int Size(SizeType type) {
    switch (type) {
    case FLOAT:
      return sizeof(float);
    case UNSIGNED_INT:
      return sizeof(unsigned int);
    case UNSIGNED_BYTE:
      return 1;
    case FACE:
      return sizeof(Face);
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
