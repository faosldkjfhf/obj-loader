#pragma once

#include <GL/glew.h>

class IndexBuffer {
public:
  IndexBuffer(const unsigned int *data, size_t count);
  ~IndexBuffer();
  void Bind();
  void Unbind();
  inline size_t Count() const { return _count; }

private:
  unsigned int _rendererId;
  size_t _count;
};
