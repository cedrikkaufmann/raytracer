/*
* IMPLEMENT ME!
*
*/
#include "light/spotlight.h"
#include "scene/scene.h"

#include "primitive/primitive.h"

SpotLight::SpotLight() {}

SpotLight::SpotLight(Vector3d const& position, Vector3d const& direction,
          float alphaMin, float alphaMax,
          float intensity, Color const& color)
    : Light(intensity, color) , position(position){

    this->alphaMin = alphaMin;
    this->alphaMax = alphaMax;
    this->direction = direction;
}


Light::Illumination SpotLight::illuminate(Ray const& ray) const {
  Vector3d const offset = ray.primitive->normalFromRay(ray)*EPSILON;
  Vector3d const target = ray.origin + ray.length*ray.direction + offset;

  // Illumination object
  Illumination illum;
  illum.direction = normalized(target - this->position);
  float alpha = acos(dotProduct(illum.direction, normalized(this->direction))) * 180/PI;

  // Precompute the distance from the light source
  float const distance = length(target - this->position);

  // Define a secondary ray from the surface point to the light source.
  Ray lightRay;
  lightRay.origin = target;
  lightRay.direction = -illum.direction;
  lightRay.length = distance-EPSILON;

  // If the target is not in shadow...
  if (!this->parentScene_->findOcclusion(&lightRay)) {
   float amin = this->alphaMin;
    float amax = this->alphaMax;

    if (std::abs(alpha) < amin) {
        alpha = 1;
    } else if (std::abs(alpha) > amax) {
        alpha = 0.0;
    } else {
        alpha = 1 -((std::abs(alpha) - amin) / (amax -amin));
    }
    // ... compute the attenuation and light color
    illum.color = 1.0f/(distance*distance) * this->color_*this->intensity_ * alpha;
  }
  return illum;
}
