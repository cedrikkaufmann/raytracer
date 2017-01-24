#include "shader/refractionshader.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

RefractionShader::RefractionShader(double reflectionAttenuation, double indexInside,
                                   double indexOutside)
  :reflectionAttenuation(reflectionAttenuation),indexInside(indexInside),indexOutside(indexOutside){}

Color RefractionShader::shade(Ray * ray) const {
  // Get the normal of the primitive which was hit
  Vector3d normalVector = ray->primitive->normalFromRay(*ray);

  // Calculate the index of refraction
  float refractiveIndex = indexInside/indexOutside;
  // What if we are already inside the object?
  if (dotProduct(normalVector, ray->direction) > 0) {
    normalVector = (-1)*normalVector;
    refractiveIndex = indexOutside/indexInside;
  }

  // Using the notation from the lecture
  float cosineTheta = dotProduct(normalVector, (-1)*ray->direction);
  float cosinePhi = std::sqrt(1 + refractiveIndex * refractiveIndex * (cosineTheta * cosineTheta - 1));
  // Calculate t, the new ray direction
  Vector3d t = refractiveIndex * ray->direction + (refractiveIndex * cosineTheta - cosinePhi) * normalVector;

  ray->origin = ray->origin + (ray->length+EPSILON)*ray->direction;
  // Check whether it is a refraction.
  if (dotProduct(t, normalVector) <= 0.0){
    ray->direction = normalized(t);
  }
  // Otherwise, it is a total reflection.
  else {
    // Next we get the reflection vector
    Vector3d const reflectionVector = ray->direction - 2*dotProduct(normalVector,ray->direction)*normalVector;

    // Change the ray direction and origin
    ray->direction = normalized(reflectionVector);
  }

  // Reset the ray
  ray->length = INFINITY;
  ray->primitive = 0;

  // Send out a new refracted ray into the scene
  return this->parentScene_->traceRay(ray);
}

bool RefractionShader::isTransparent() const {
  return true;
}
