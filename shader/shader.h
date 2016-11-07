#ifndef SHADER_H
#define SHADER_H

#include "common/color.h"
#include "common/ray.h"

// Forward declarations
class Scene;

class Shader {
  friend class Scene;

public:
  // Constructor / Desctructor
  Shader() {}
  virtual ~Shader() {}

  // Get
  virtual bool isTransparent() const { return false; }

  // Shader functions
  virtual Color shade(Ray * ray) const = 0;

protected:
  Scene * parentScene_;

};

#endif
