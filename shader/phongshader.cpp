#include "shader/phongshader.h"
#include "light/light.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

PhongShader::PhongShader(float diffuseCoefficient, float specularCoefficient,
                         float shininessExponent, Color const& objectColor)
  : objectColor(objectColor),
    diffuseCoefficient(diffuseCoefficient),
    specularCoefficient(specularCoefficient),
    shininessExponent(shininessExponent) {}

Color PhongShader::shade(Ray * ray) const {
    // First we get the normal of the primitive, which was hit
    Vector3d normalVector = ray->primitive->normalFromRay(*ray);

    // Compute illumination
    Color illuminationColor;
    std::vector<Light*> lights = this->parentScene_->lights();
    for (unsigned int i = 0; i < lights.size(); ++i) {
        Light::Illumination illum;
        illum = lights.at(i)->illuminate(*ray);

        // Diffuse term.
        Color const diffuseColor = std::max(dotProduct((-1)*illum.direction, normalVector),0.0f)
                * diffuseCoefficient* illum.color;
        illuminationColor = illuminationColor + diffuseColor;

        // Specular term (based on reflection vector).
        Vector3d const& reflectionVector = ray->direction - 2*dotProduct(normalVector,ray->direction)*normalVector;
        float cosine = dotProduct((-1)*illum.direction, reflectionVector);
        if (cosine > 0) {
            Color specularColor = specularCoefficient*Color(1, 1, 1)  // white highlight
                    * powf(cosine, shininessExponent) // shininess factor
                    * illum.color;
            illuminationColor = illuminationColor + specularColor;
        }
    }
    return illuminationColor * this->objectColor;
}
