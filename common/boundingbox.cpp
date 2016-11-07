#include <algorithm>
#include "common/boundingbox.h"
#include "common/ray.h"

bool BoundingBox::intersects(Ray const& ray) const {
 /*
  * IMPLEMENT ME!
  *
  * Intersect the ray with the bounding box.
  * Return true if the ray would intersect the box, otherwise return false.
  *
  */
  return false;
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
