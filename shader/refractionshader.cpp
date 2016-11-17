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


  //berechne das t
  float mue = indexOutside / indexInside;

  float discriminant = (1 - mue*mue)*(1-pow(dotProduct(ray->direction, normalVector),2));

  Vector3d t;

  if (discriminant < 0) {
    // total refelction

    t = Vector3d(0,0,0);
  } else {
    float gamma1 = -mue * dotProduct(ray->direction, normalVector) + sqrt(discriminant);
    float gamma2 = gamma1 = -mue * dotProduct(ray->direction, normalVector) - sqrt(discriminant);

    //welches gamma nehme ich hier?
    t = mue * ray->direction + gamma1 * normalVector;
  }

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
