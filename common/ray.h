#ifndef RAY_H
#define RAY_H

#include "common/common.h"
#include "common/vector2d.h"
#include "common/vector3d.h"

// Forward declaration
class Primitive;

struct Ray {
  // Components
  Vector3d origin; // o
  Vector3d direction; // d
  Vector3d invDirection = Vector3d(1/direction.x, 1/direction.y, 1/direction.z);
  float length; // t
  Primitive const* primitive;
  Vector2d surfacePosition;
  int remainingBounces; // how often the ray is allowed to bounce

  // Constructor
  Ray()
    : length(INFINITY), primitive(nullptr), remainingBounces(4) {}
};

#endif
