#include <algorithm>
#include "common/boundingbox.h"
#include "common/ray.h"

bool BoundingBox::intersects(Ray const& ray) const {
  //Using Smit's algorithm
  Vector3d invDirection(1 / ray.direction.x, 1 / ray.direction.y, 1 / ray.direction.z);

  Vector3d bounds[2];
  bounds[0] = minimumCorner;
  bounds[1] = maximumCorner;

  int sign[3];
  sign[0] = (invDirection.x < 0);
  sign[1] = (invDirection.y < 0);
  sign[2] = (invDirection.z < 0);

  float tmin, tmax, tymin, tymax, tzmin, tzmax;

  tmin = (bounds[sign[0]].x - ray.origin.x) * invDirection.x;
  tmax = (bounds[1-sign[0]].x - ray.origin.x) * invDirection.x;
  tymin = (bounds[sign[1]].y - ray.origin.y) * invDirection.y;
  tymax = (bounds[1-sign[1]].y - ray.origin.y) * invDirection.y;

  if ( (tmin > tymax) || (tymin > tmax) )
    return false;
  if (tymin > tmin)
    tmin = tymin;
  if (tymax < tmax)
    tmax = tymax;

  tzmin = (bounds[sign[2]].z - ray.origin.z) * invDirection.z;
  tzmax = (bounds[1-sign[2]].z - ray.origin.z) * invDirection.z;

  if ( (tmin > tzmax) || (tzmin > tmax) )
    return false;
  if (tzmin > tmin)
    tmin = tzmin;
  if (tzmax < tmax)
    tmax = tzmax;

  return true;
}

float BoundingBox::length(int dimension) {
  return this->maximumCorner[dimension] - this->minimumCorner[dimension];
}


// Comparison operators ////////////////////////////////////////////////////////

bool operator==(BoundingBox const& left, BoundingBox const& right) {
  return (left.minimumCorner == right.minimumCorner
          && left.maximumCorner == right.maximumCorner);
}

bool operator!=(BoundingBox const& left, BoundingBox const& right) {
  return !(left == right);
}
