#ifndef BRDFSHADER_H
#define BRDFSHADER_H

#include "shader/shader.h"

// Forward declarations
class BRDFRead;

class BrdfShader : public Shader {

public:
  // Constructor
  BrdfShader(char const* fileName, Color const& scale);

  // Shader functions
  virtual Color shade(Ray * ray) const;

private:
  Color scale;
  BRDFRead * brdf;

};

#endif
