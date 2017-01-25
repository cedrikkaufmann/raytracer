#ifndef TOONSHADER_H
#define TOONSHADER_H

#include "shader.h"

class ToonShader : public Shader
{
public:
    ToonShader(float shininessExponent,
               Color const& objectColor);

    // Shader functions
    virtual Color shade(Ray * ray) const;

protected:
  float shininessExponent;
  Color objectColor;
};

#endif // TOONSHADER_H
