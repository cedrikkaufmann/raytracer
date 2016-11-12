#include "shader/lambertshader.h"
#include "light/light.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

LambertShader::LambertShader(Color const& objectColor)
  : objectColor(objectColor) {}

Color LambertShader::shade(Ray * ray) const {
  Color illuminationColor; 
  
 /*
  * IMPLEMENT ME!
  *
  * First, get the normal of the primitive, which was hit
  * Sum the light over all light sources
  * Use the Lambert formula
  * 
  */

  return illuminationColor * this->objectColor;
}
