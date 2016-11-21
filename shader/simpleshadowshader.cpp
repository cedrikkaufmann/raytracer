#include "shader/simpleshadowshader.h"
#include "light/light.h"
#include "scene/scene.h"

SimpleShadowShader::SimpleShadowShader(Color const& objectColor)
  : objectColor(objectColor) {}

Color SimpleShadowShader::shade(Ray * ray) const {
  // Accumulate the light over all light sources
  Color illuminationColor;
  std::vector<Light*> lights = this->parentScene_->lights();
  for (unsigned int i = 0; i < lights.size(); ++i) {
    Light::Illumination const illum = lights.at(i)->illuminate(*ray);
    illuminationColor += illum.color;
  }
  return illuminationColor * this->objectColor;
}
