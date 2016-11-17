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

  //hier hab ich angefangen

  //berechne das t
  double mue = indexOutside / indexInside;
  double gamma1 = -mue * dotProduct(ray->direction, normalVector) + sqrt((1 - mue*mue)*(1-pow(dotProduct(ray->direction, normalVector),2)));
  double gamma2 = gamma1 = -mue * dotProduct(ray->direction, normalVector) - sqrt((1 - mue*mue)*(1-pow(dotProduct(ray->direction, normalVector),2)));
  //welches gamma nehme ich hier?
  Vector3d t = mue * ray->direction + gamma1 * normalVector;

  //bis hier hab ich gemacht
  ray->direction = t;

  // Reset the ray
  ray->length = INFINITY;
  ray->primitive = 0;

  // Send out a new refracted ray into the scene
  return this->parentScene_->traceRay(ray);
}

bool RefractionShader::isTransparent() const {
  return true;
}
