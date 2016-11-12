#ifndef REFRACTIONSHADER_H
#define REFRACTIONSHADER_H

#include "shader/shader.h"

class RefractionShader : public Shader {

public:
  // Constructor
  RefractionShader(double reflectionAttenuation = 0.4,
                   double indexInside = 1,
                   double indexOutside = 1);

  // Shader functions
  virtual Color shade(Ray * ray) const;
  virtual bool isTransparent() const;

private:
  double reflectionAttenuation;
  double indexInside;
  double indexOutside;

};

#endif
