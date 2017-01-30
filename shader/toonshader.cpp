#include "toonshader.h"
#include "light/light.h"
#include "primitive/primitive.h"
#include "scene/scene.h"
#include "common/vector3d.h"

#include <iostream>

ToonShader::ToonShader(int colorLevels,
                       float edgeThreshold, float specularThreshold,
                       float diffuseCoefficient, float specularCoefficient,
                       float shininessExponent, Color const& objectColor)
    : objectColor(objectColor),
      colorLevels(colorLevels),
      edgeThreshold(edgeThreshold),
      specularThreshold(specularThreshold),
      diffuseCoefficient(diffuseCoefficient),
      specularCoefficient(specularCoefficient),
      shininessExponent(shininessExponent) {}

Color ToonShader::shade(Ray * ray) const {
    // First we get the normal of the primitive, which was hit
    Vector3d normalVector = ray->primitive->normalFromRay(*ray);
    Color illuminationColor;

    if ( std::abs(dotProduct(ray->direction, normalVector)) < edgeThreshold ) {
        // edge detected
        return Color(0,0,0);
    } else {
        float scaleFactor = 1.0f / colorLevels;

        // Compute illumination
        std::vector<Light*> lights = this->parentScene_->lights();

        for (unsigned int i = 0; i < lights.size(); ++i) {
            Light::Illumination illum;
            illum = lights.at(i)->illuminate(*ray);

            // Diffuse term.
            float const diffuse = std::max(dotProduct((-1)*illum.direction, normalVector),0.0f);
            Color const diffuseColor = floor(diffuse * colorLevels) * scaleFactor * diffuseCoefficient * illum.color;
            illuminationColor += diffuseColor;

            // Specular term (based on reflection vector).
            Vector3d const& reflectionVector = ray->direction - 2*dotProduct(normalVector,ray->direction)*normalVector;
            float cosine = dotProduct((-1)*illum.direction, reflectionVector);
            if (cosine > 0) {
                float const specular = powf(cosine, shininessExponent);

                if (specular > specularThreshold) {
                    Color specularColor = specularCoefficient*Color(1, 1, 1)  // white highlight
                            * specular // shininess factor
                            * illum.color;
                    illuminationColor += specularColor;
                }
            }
        }

        return (illuminationColor + this->objectColor);
    }
}
