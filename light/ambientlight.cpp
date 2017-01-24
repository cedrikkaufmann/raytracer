#include "light/ambientlight.h"
#include "primitive/primitive.h"

AmbientLight::AmbientLight(float intensity, Color const& color)
  : Light(intensity, color) {}

Light::Illumination AmbientLight::illuminate(Ray const& ray) const {
  return {
    this->color_ * this->intensity_,
    (-1) * ray.primitive->normalFromRay(ray)
  };
}
