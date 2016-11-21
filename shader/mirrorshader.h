#ifndef MIRRORSHADER_H
#define MIRRORSHADER_H

#include "shader/shader.h"

class MirrorShader : public Shader {

public:
  // Constructor
  MirrorShader();

  // Shader functions
  virtual Color shade(Ray * ray) const;

};

#endif
