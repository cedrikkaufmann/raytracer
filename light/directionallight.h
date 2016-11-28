#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "light/light.h"

class DirectionalLight : public Light {

public:
  // Constructor
  DirectionalLight();
  DirectionalLight(Vector3d const& direction, float intensity, Color const& color = Color(1,1,1));

  // Get
  Vector3d getDirection() const { return this->direction; }

  // Set
  void setDirection(Vector3d const& direction) { this->direction = normalized(direction); }

  // Light functions
  virtual Illumination illuminate(Ray const& ray) const;

protected:
  Vector3d direction;

};

#endif
