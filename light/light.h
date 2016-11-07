#ifndef LIGHT_H
#define LIGHT_H

#include "common/ray.h"
#include "common/color.h"

// Forward declarations
class Scene;

class Light {
  friend class Scene;

public:
  // Illumination object
  struct Illumination {
    Color color;
    Vector3d direction;
  };

  // Constructor / Destructor
  Light(float intensity = 0.0f, Color const& color = Color(1,1,1))
    : color_(color), intensity_(intensity) {}
  virtual ~Light() {}

  // Get
  Color color() const { return this->color_; }
  float intensity() const { return this->intensity_; }

  // Set
  void setColor(Color const& color) { this->color_ = color; }
  void setIntensity(float intensity) { this->intensity_ = intensity; }

  // Light functions
  virtual Illumination illuminate(Ray const& ray) const = 0;

protected:
  Scene * parentScene_;
  Color color_;
  float intensity_;

};

#endif
