#include "shader/phongshader.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

PhongShader::PhongShader(float diffuseCoefficient, float specularCoefficient, float shininessExponent, Color const& objectColor)
    : diffuseCoefficient(diffuseCoefficient), specularCoefficient(specularCoefficient), shininessExponent(shininessExponent),
      objectColor(objectColor) {}

Color PhongShader::shade(Ray * ray) const {

}
