#include <cmath>
#include "shader/materialshader.h"
#include "light/light.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

Vector3d normalInTangentSpace(Vector3d const& surfaceNormal,
                              Vector3d const& textureNormal) {
  Vector3d const axis = crossProduct(Vector3d(0,0,1),surfaceNormal);
  float const sine = length(axis);
  float const cosine = dotProduct(Vector3d(0,0,1),surfaceNormal);
  float const s = (1.0-cosine)/(sine*sine);

  // Determine the rotation matrix R
  Vector3d vMat[3] = { // NOTE: we use row-wise vectors, for sanity purposes
                       Vector3d(    0.0f, -axis.z, +axis.y ),
                       Vector3d( +axis.z,    0.0f, -axis.x ),
                       Vector3d( -axis.y, +axis.x,    0.0f )
                     };
  Vector3d const vMat2[3] = {
    Vector3d( -axis.y*axis.y-axis.z*axis.z,   axis.x*axis.y,   axis.x*axis.z )*s,
    Vector3d( axis.x*axis.y,   -axis.x*axis.x-axis.z*axis.z,   axis.y*axis.z )*s,
    Vector3d( axis.x*axis.z,   axis.y*axis.z,   -axis.x*axis.x-axis.y*axis.y )*s
  };
  Vector3d const R[3] = {
    Vector3d(1,0,0) + vMat[0] + vMat2[0],
    Vector3d(0,1,0) + vMat[1] + vMat2[1],
    Vector3d(0,0,1) + vMat[2] + vMat2[2],
  };
  return Vector3d(
        dotProduct(R[0],textureNormal),
      dotProduct(R[1],textureNormal),
      dotProduct(R[2],textureNormal));
}

MaterialShader::MaterialShader(Color const& objectColor)
  : objectColor(objectColor),
    opacity(1.0f),
    normalCoefficient(1.0f),
    diffuseCoefficient(0.5f),
    specularCoefficient(0.0f), shininessExponent(10) {}

Color MaterialShader::shade(Ray * ray) const {
  // Texture coordinates
  Vector2d surfacePosition = ray->primitive->uvFromRay(*ray);

  // Normal vector
  Vector3d normal = ray->primitive->normalFromRay(*ray);

  // Compute fragment color
  Color fragmentColor;
  std::vector<Light*> lights = this->parentScene_->lights();
  for (unsigned int i = 0; i < lights.size(); ++i) {

    // Retrieve an illumination object
    Light::Illumination illum = lights.at(i)->illuminate(*ray);

    // Diffuse term (lambert)
    Color const diffuseColor = std::max(dotProduct(-illum.direction,normal), 0.0f)
        * this->diffuseCoefficient*illum.color;
    if (!this->diffuseMap.isNull())
      fragmentColor += diffuseColor*this->diffuseMap.color(surfacePosition);
    else
      fragmentColor += diffuseColor*this->objectColor;

    //Alpha term
    Color color = alphaMap.color(surfacePosition.u, surfacePosition.v);
    float const average = (color.r + color.b + color.g) / 3.0f;
    setOpacity(1.0f - average);
  }

  return fragmentColor;
}

bool MaterialShader::isTransparent() const {
  return !this->alphaMap.isNull();
}
