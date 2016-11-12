#include "shader/simpleshadowshader.h"
#include "light/light.h"
#include "scene/scene.h"

SimpleShadowShader::SimpleShadowShader(Color const& objectColor)
  : objectColor(objectColor) {}

Color SimpleShadowShader::shade(Ray * ray) const {
  Color illuminationColor;
  
  /*
  * IMPLEMENT ME!
  *
  * Sum the light over all light sources
  */
  
  return illuminationColor * this->objectColor;
}
