#include "shader/mirrorshader.h"
#include "primitive/primitive.h"
#include "scene/scene.h"

Color MirrorShader::shade(Ray * ray) const {
	
 /*
  * IMPLEMENT ME!
  *
  * Get the normal of the primitive, which was hit
  * Get the reflection vector
  * Change the ray direction and origin
  * Reset the ray
  * Send out a new mirrored ray into the scene
  * 
  *
  */
  Vector3d normal = ray->primitive->normalFromRay(*ray);
  Vector3d reflection = ray->direction - 2 * dotProduct(normal, ray->direction) * normal;

  ray->origin = ray->origin + ray->direction * ray->length;
  ray->direction = reflection;
  ray->primitive = nullptr;
  ray->length = INFINITY;

  parentScene_->traceRay(ray);

  return Color();
}
