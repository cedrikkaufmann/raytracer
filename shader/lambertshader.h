#ifndef LAMBERTSHADER_H
#define LAMBERTSHADER_H

#include "shader/shader.h"

class LambertShader : public Shader {

public:
  // Constructor
  LambertShader(Color const& objectColor);

  // Shader functions
  virtual Color shade(Ray * ray) const;

protected:
  Color objectColor;

};

#endif
