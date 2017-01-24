#include "shader/brdfshader.h"
#include "common/brdfread.h"
#include "light/light.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

BrdfShader::BrdfShader(char const* fileName, Color const& scale)
  : scale(scale) {
  this->brdf = new BRDFRead(fileName);
}

Color BrdfShader::shade(Ray * ray) const {
  // First we get the normal of the primitive, which was hit
  Vector3d const normalVector = ray->primitive->normalFromRay(*ray);

  Color illuminationColor;

  // Calculate theta and phi
  float thetaIn = std::acos(dotProduct((-1)*normalVector, ray->direction));
  float phiIn = 0.0f;

  std::vector<Light*> lights = this->parentScene_->lights();
  for (unsigned int i = 0; i < lights.size(); ++i) {
    Light::Illumination illum;
    illum = lights.at(i)->illuminate(*ray);

    // Diffuse term
    float const cosine = dotProduct((-1)*illum.direction, normalVector);
    if (cosine > 0) {
      Color color;

      // Avoid numeric instability
      if (cosine < 1) {
        float const thetaOut = std::acos(cosine);

        // Derive local coordinate system
        Vector3d const x = crossProduct((-1)*ray->direction, normalVector);
        Vector3d const y = crossProduct(normalVector, x);

        // Project outgoing vector into local coordinate system
        Vector3d const c = crossProduct((-1)*illum.direction, normalVector);
        float const phiOut = std::atan2(dotProduct(c,y),dotProduct(c,x));

        color = Color(brdf->lookupBrdfValues(thetaIn, phiIn, thetaOut, phiOut));
      } else {
        color = Color(brdf->lookupBrdfValues(thetaIn, phiIn, 0, 0));
      }

      // Calculate colors
      Color const diffuseColor = scale*color * cosine;
      illuminationColor += diffuseColor * illum.color;
    }

  }
  return illuminationColor;
}
