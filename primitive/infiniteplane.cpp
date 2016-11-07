#include <cmath>
#include "primitive/infiniteplane.h"


// Constructor /////////////////////////////////////////////////////////////////

InfinitePlane::InfinitePlane(Shader * shader)
  : Primitive(shader), normal_(0,1,0) {}

InfinitePlane::InfinitePlane(Vector3d const& origin, Vector3d const& normal, Shader * shader)
  : Primitive(shader), origin_(origin), normal_(normal) {}


// Primitive functions /////////////////////////////////////////////////////////

bool InfinitePlane::intersect(Ray * ray) const {
 /*
  * IMPLEMENT ME!
  *
  * Our raytracer will iterate over all primitives in the scene.
  * This function tests whether a given ray intersects this primitive.
  * If the ray intersects this primitive, and if this primitive is closest to
  * the origin of the ray, then we need to save that information to the ray.
  *
  * First, determine whether the ray intersects this object. Next, calculate
  * the minimum distance from the ray's origin to the primitive's surface.
  * If this distance is shorter than the ray's length, than this is the
  * closest primitive to the camera (so far).
  *
  * Save that information to the ray by using:
  *
  *  ray->length = distance;  // The new (shorter) length of the ray
  *  ray->primitive = this;   // The primitive that is hit by the ray
  *
  * Also return true/false, whether the primitive was hit or not respectively.
  *
  */

  /*
   * Calculating intersect using normal form of pane equation
   * Seperation of solving fraction to check denominator against zero
   *
   */

  float equation_denominator = dotProduct(ray->direction, normal_);
  //(ray->direction.x * normal_.x + ray->direction.y * normal_.y + ray->direction.z * normal_.z);

  if (equation_denominator != 0) {
      float equation_numerator = dotProduct((ray->origin - origin_), normal_) * (-1);
      //float equation_numerator = ((ray->origin.x - origin_.x) * normal_.x + (ray->origin.y - origin_.y) * normal_.y+(ray->origin.z - origin_.z) * normal_.z) * (-1);

      float fraction_value = equation_numerator / equation_denominator;

      // Calculate point of intersection
      Vector3d fraction = Vector3d(fraction_value, fraction_value, fraction_value);
      Vector3d intersection = ray->origin + componentProduct(fraction, ray->direction);

      // Check if shorter than previous
      if (float distance = length(intersection) < ray->length) {
          ray->length = distance;
          ray->primitive = this;
      }

      return true;
  } else {
      return false;
  }
}

Vector3d InfinitePlane::normalFromRay(Ray const& ray) const {
 /*
  * IMPLEMENT ME!
  *
  * This function should return the surface normal at the point that is
  * hit by the given ray.
  *
  */
  return Vector3d();
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
