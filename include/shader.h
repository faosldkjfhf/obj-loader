#pragma once

#include <string>

class Shader {
public:
  Shader(unsigned int type, const std::string &file);

  void Bind(unsigned int program) const;
  void Unbind(unsigned int program) const;

  unsigned int CompileShader();
  std::string LoadAsString() const;

  inline unsigned int Location() const { return _id; }

private:
  unsigned int _id;
  std::string _file;
  unsigned int _type;
};
