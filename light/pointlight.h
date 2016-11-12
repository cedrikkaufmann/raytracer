#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light/light.h"

class PointLight : public Light {

public:
  // Constructor
  PointLight();
  PointLight(Vector3d const& position, float intensity, Color const& color = Color(1,1,1));

  // Get
  Vector3d getPosition() const { return this->position; }

  // Set
  void setPosition(Vector3d const& position) { this->position = position; }

  // Light functions
  virtual Illumination illuminate(Ray const& ray) const;

protected:
  Vector3d position;

};

#endif
