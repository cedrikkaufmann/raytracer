#ifndef TOONSHADER_H
#define TOONSHADER_H

#include "shader.h"

class ToonShader : public Shader
{
public:
    ToonShader();

    // Shader functions
    virtual Color shade(Ray * ray) const;
};

#endif // TOONSHADER_H
