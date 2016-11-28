#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "shader/shader.h"

class PhongShader : public Shader {

public:
  // Constructor
  PhongShader(float diffuseCoefficient,
              float specularCoefficient,
              float shininessExponent,
              Color const& objectColor);

  // Shader functions
  virtual Color shade(Ray * ray) const;

private:
  Color objectColor;
  float diffuseCoefficient;
  float specularCoefficient;
  float shininessExponent;

};

#endif
