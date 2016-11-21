#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "light/light.h"

class AmbientLight : public Light {

public:
  // Constructor
  AmbientLight(float intensity = 0.0f, Color const& color = Color(1,1,1));

  // Light functions
  virtual Illumination illuminate(Ray const& ray) const;

};

#endif
