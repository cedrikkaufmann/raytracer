#include "shader/mirrorshader.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

MirrorShader::MirrorShader() {}

Color MirrorShader::shade(Ray * ray) const {
  // Get the normal of the primitive, which was hit
  Vector3d const normalVector = ray->primitive->normalFromRay(*ray);

  // Get the reflection vector
  Vector3d const reflectionVector = ray->direction - 2*dotProduct(normalVector,ray->direction)*normalVector;

  // Change the ray direction and origin
  ray->origin = ray->origin + (ray->length-EPSILON)*ray->direction;
  ray->direction = normalized(reflectionVector);

  // Reset the ray
  ray->length = INFINITY;
  ray->primitive = 0;

  // Send out a new mirrored ray into the scene
  return this->parentScene_->traceRay(ray);
}
