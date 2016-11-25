#include "scene/scene.h"
#include "light/ambientlight.h"
#include "primitive/primitive.h"

/*
AmbientLight::AmbientLight() {

}

AmbientLight::AmbientLight(float intensity, const Color &color)
     {}

Light::Illumination SpotLight::illuminate(Ray const& ray) const {

}*/

//AmbientLight::AmbientLight() {}
AmbientLight::AmbientLight(float intensity, Color const& color)
    : Light(intensity, color) {}
Light::Illumination AmbientLight::illuminate(Ray const& ray) const {}

