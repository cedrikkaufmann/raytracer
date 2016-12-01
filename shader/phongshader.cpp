#include "shader/phongshader.h"
#include "primitive/primitive.h"
#include "scene/scene.h"
#include "light/light.h"

PhongShader::PhongShader(float diffuseCoefficient, float specularCoefficient, float shininessExponent, Color const& objectColor)
    : diffuseCoefficient(diffuseCoefficient), specularCoefficient(specularCoefficient), shininessExponent(shininessExponent),
      objectColor(objectColor) {}

Color PhongShader::shade(Ray * ray) const {
    /* get shading normal */
    Vector3d normal = ray->primitive->normalFromRay(*ray);

    /* turn normal to front */
    if (dotProduct(normal, ray->direction) > 0)
    {
        normal = -normal;
    }

    /* calculate reflection vector */
    Vector3d reflect = ray->direction - 2 * dotProduct(normal, ray->direction) * normal;

    Color result = objectColor;

    /* shadow ray starting from surface point */
    Ray shadow;
    shadow.origin = ray->origin + ray->length * ray->direction;

    /* iterate over all light sources */
    for (unsigned int l=0; l< this->parentScene_->lights().size(); l++)
    {
        /* get directionection to light, and intensity */
        //this->parentScene_->lights()[l]->illuminate(shadow);
        /* diffuse term */
        float cosLightNormal = dotProduct(shadow.direction, normal);

        if (cosLightNormal > 0) {
            if (this->parentScene_->findOcclusion(&shadow))
            {
                continue;
            }

            Color diffuseColor = diffuseCoefficient * objectColor;
            result = result + diffuseColor * cosLightNormal * this->parentScene_->lights()[l]->intensity();
        }

        /* specular term */
        float cosLightReflect = dotProduct(shadow.direction, reflect);
        if (cosLightReflect > 0)
        {
            Color specularColor = specularCoefficient * Color(1,1,1); // white highlight;
            result = result + specularColor * powf(cosLightReflect, shininessExponent) * this->parentScene_->lights()[l]->intensity();
        }
    }

    return result;

}
