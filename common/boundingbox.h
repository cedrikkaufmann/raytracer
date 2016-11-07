#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "common/vector3d.h"

// Forward declarations
class Ray;

struct BoundingBox {
  // Components
  Vector3d minimumCorner, maximumCorner;

  // Constructor
  BoundingBox() {}
  BoundingBox(Vector3d const& minimumCorner, Vector3d const& maximumCorner)
    : minimumCorner(minimumCorner), maximumCorner(maximumCorner) {}

  bool intersects(Ray const& ray) const;
  float length(int dimension);
};

// Comparison operators
bool operator==(BoundingBox const& left, BoundingBox const& right);
bool operator!=(BoundingBox const& left, BoundingBox const& right);

#endif
