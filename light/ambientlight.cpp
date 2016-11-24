#include "scene/scene.h"
#include "ambientlight.h"
#include "primitive/primitive.h"

AmbientLight::AmbientLight() {}

AmbientLight::AmbientLight(float intensity, const Color &color)
    : Light(intensity, color), position(position) {}

Light::Illumination AmbientLight::illuminate(Ray const& ray) {

}
