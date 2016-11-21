#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light/light.h"

class SpotLight : public Light {

public:
  // Constructor
  SpotLight();
  SpotLight(Vector3d const& position, Vector3d const& direction,
            float alphaMin, float alphaMax,
            float intensity, Color const& color = Color(1,1,1));

  // Get
  Vector3d getDirection() const { return this->direction; }
  Vector3d getPosition() const { return this->position; }
  float getAlphaMax() const { return this->alphaMax; }
  float getAlphaMin() const { return this->alphaMin; }

  // Set
  void setDirection(Vector3d const& direction) { this->direction = normalized(direction); }
  void setPosition(Vector3d const& position) { this->position = position; }
  void setAlphaMax(float alphaMax) { this->alphaMax = alphaMax; }
  void setAlphaMin(float alphaMin) { this->alphaMin = alphaMin; }

  // Light functions
  virtual Illumination illuminate(Ray const& ray) const;

protected:
  Vector3d position;
  Vector3d direction;
  float alphaMin, alphaMax;

};

#endif
