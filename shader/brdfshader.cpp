#include "shader/brdfshader.h"
#include "common/brdfread.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

BrdfShader::BrdfShader(char const* fileName, Color const& scale)
    : scale(scale) {
    brdf = new BRDFRead(fileName);
}

Color BrdfShader::shade(Ray * ray) const {

}
