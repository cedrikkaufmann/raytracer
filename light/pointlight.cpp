#include "light/pointlight.h"
#include "scene/scene.h"

#include "primitive/primitive.h"

PointLight::PointLight() {}

PointLight::PointLight(Vector3d const& position, float intensity, Color const& color)
    : Light(intensity, color), position(position) {}

Light::Illumination PointLight::illuminate(Ray const& ray) const {
  Vector3d const offset = ray.primitive->normalFromRay(ray)*EPSILON;
  Vector3d const target = ray.origin + ray.length*ray.direction + offset;

  // Illumination object
  Illumination illum;
  illum.direction = normalized(target - this->position);

  // Precompute the distance from the light source
  float const distance = length(target - this->position);

  // Define a secondary ray from the surface point to the light source.
  Ray lightRay;
  lightRay.origin = target;
  lightRay.direction = (-1) * illum.direction;
  lightRay.length = distance-EPSILON;

  // If the target is not in shadow...
  if (!this->parentScene_->findOcclusion(&lightRay))
    // ... compute the attenuation and light color
    illum.color = 1.0f/(distance*distance) * this->color_*this->intensity_;
  return illum;
}
