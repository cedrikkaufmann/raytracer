#ifndef TOONSHADER_H
#define TOONSHADER_H

#include "shader.h"

class ToonShader : public Shader
{
public:
    ToonShader(int colorLevels,
               float edgeThreshold,
               float specularThreshold,
               float diffuseCoefficient,
               float specularCoefficient,
               float shininessExponent,
               Color const& objectColor);

    // Shader functions
    virtual Color shade(Ray * ray) const;

protected:
  Color objectColor;
  int colorLevels;
  float edgeThreshold;
  float specularThreshold;
  float diffuseCoefficient;
  float specularCoefficient;
  float shininessExponent;
};

#endif // TOONSHADER_H
