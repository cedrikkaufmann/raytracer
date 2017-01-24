#include "shader/lambertshader.h"
#include "light/light.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

LambertShader::LambertShader(Color const& objectColor)
  : objectColor(objectColor) {}

Color LambertShader::shade(Ray * ray) const {
  // First we get the normal of the primitive, which was hit
  Vector3d const normalVector = ray->primitive->normalFromRay(*ray);

  // Accumulate the light over all light sources
  Color illuminationColor;
  std::vector<Light*> lights = this->parentScene_->lights();
  for (unsigned int i = 0; i < lights.size(); ++i) {
    Light::Illumination const illum = lights.at(i)->illuminate(*ray);
    // Lambert formula
    float const cosine = dotProduct((-1)*illum.direction, normalVector);
    illuminationColor += std::max(cosine,0.0f)*illum.color;
  }
  return illuminationColor * this->objectColor;
}
