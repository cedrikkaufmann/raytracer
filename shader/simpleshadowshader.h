#ifndef SIMPLESHADOWSHADER_H
#define SIMPLESHADOWSHADER_H

#include "shader/shader.h"

class SimpleShadowShader : public Shader {

public:
  // Constructor
  SimpleShadowShader(Color const& objectColor);

  // Shader functions
  virtual Color shade(Ray * ray) const;

private:
  Color objectColor;

};

#endif
