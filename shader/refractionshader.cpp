#include "shader/refractionshader.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

RefractionShader::RefractionShader(double reflectionAttenuation, double indexInside,
                                   double indexOutside)
  :reflectionAttenuation(reflectionAttenuation),indexInside(indexInside),indexOutside(indexOutside){}

Color RefractionShader::shade(Ray * ray) const {
  // Get the normal of the primitive which was hit
  Vector3d normalVector = ray->primitive->normalFromRay(*ray);

  /*
  * IMPLEMENT ME!
  *
  * Calculate the index of refraction
  * What if we are already inside the object?
  * Using the notation from the lecture
  * Calculate t, the new ray direction
  * Check whether it is a refraction
  * Otherwise, it is a total reflection
  * Next we get the reflection vector
  * Change the ray direction and origin
  *
  */

  // Reset the ray
  ray->length = INFINITY;
  ray->primitive = 0;

  // Send out a new refracted ray into the scene
  return this->parentScene_->traceRay(ray);
}

bool RefractionShader::isTransparent() const {
  return true;
}
