#include <cmath>
#include "primitive/infiniteplane.h"


// Constructor /////////////////////////////////////////////////////////////////

InfinitePlane::InfinitePlane(Shader * shader)
  : Primitive(shader), normal_(0,1,0) {}

InfinitePlane::InfinitePlane(Vector3d const& origin, Vector3d const& normal, Shader * shader)
  : Primitive(shader), origin_(origin), normal_(normal) {}


// Primitive functions /////////////////////////////////////////////////////////

bool InfinitePlane::intersect(Ray * ray) const {
  // Make sure the ray is not parallel to the plane
  float const cosine = dotProduct(ray->direction, normal_);
  if (std::fabs(cosine) < EPSILON)
    return false;

  // Determine the distance at which the ray intersects the plane
  float const t = dotProduct(origin_ - ray->origin, normal_) / cosine;

  // Test whether this is the foremost primitive in front of the camera
  if (t < EPSILON || ray->length < t)
    return false;

  // Prepare the ray
  ray->length = t;
  ray->primitive = this;
  ray->surfacePosition = Vector2d();
  return true;
}

Vector3d InfinitePlane::normalFromRay(Ray const& ray) const {
    (void)ray; // ray is unused in this case, but we do not want a warning
     return normal_;
}


// Bounding box ////////////////////////////////////////////////////////////////

float InfinitePlane::minimumBounds(int dimension) const {
  /*
  * IMPLEMENT ME!
  *
  * These values are used for determining the bounding box.
  * This should return the minimum value along the given dimension.
  *
  */
  return -INFINITY;
}

float InfinitePlane::maximumBounds(int dimension) const {
  /*
  * IMPLEMENT ME!
  *
  * These values are used for determining the bounding box.
  * This should return the maximum value along the given dimension.
  *
  */
  return +INFINITY;
}
