#include "toonshader.h"
#include "light/light.h"
#include "primitive/primitive.h"
#include "scene/scene.h"
#include "common/vector3d.h"

ToonShader::ToonShader() {}

Color ToonShader::shade(Ray * ray) const {
    float shininessExponent = 0.2f;

    // First we get the normal of the primitive, which was hit
    Vector3d normalVector = ray->primitive->normalFromRay(*ray);

    // Compute illumination
    Color illuminationColor;
    std::vector<Light*> lights = this->parentScene_->lights();
    for (unsigned int i = 0; i < lights.size(); ++i) {
        Light::Illumination illum;
        illum = lights.at(i)->illuminate(*ray);

        // Diffuse term.
        float diffuseLight = std::max(dotProduct((-1)*illum.direction, normalVector),0.0f);
        Vector3d hVec = normalized(ray->direction + illum.direction);
        float specularLight;

        if (diffuseLight <= EPSILON) {
            specularLight = 0;
        } else {
            specularLight = std::pow( std::max( dotProduct(normalVector, hVec), 0.0f ), 2 );
        }

        float edge = std::max( dotProduct(normalVector, hVec), 0.0f);
    }

    return illuminationColor;
}
