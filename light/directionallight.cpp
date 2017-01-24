#include "light/directionallight.h"
#include "scene/scene.h"

DirectionalLight::DirectionalLight()
  : direction(Vector3d(0,0,1)) {}

DirectionalLight::DirectionalLight(Vector3d const& direction, float intensity, Color const& color)
  : Light(intensity, color), direction(normalized(direction)) {}

Light::Illumination DirectionalLight::illuminate(Ray const& ray) const {
  Vector3d const target = ray.origin + (ray.length-EPSILON)*ray.direction;

  // Illumination object
  Illumination illum;
  illum.direction = this->direction;

  // Define a secondary ray from the surface point to the light source.
  Ray lightRay;
  lightRay.origin = target;
  lightRay.direction = (-1)*illum.direction;
  lightRay.length = INFINITY;

  // If the target is not in shadow...
  if (!this->parentScene_->findOcclusion(&lightRay))
    // ... compute the attenuation and light color
    illum.color = this->color_*this->intensity_;
  return illum;
}
