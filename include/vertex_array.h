#pragma once

class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void Initialize();

  void Bind() const;
  void Unbind() const;

private:
  unsigned int _id;
};
