#ifndef CAMERA_H
#define CAMERA_H

#include "common/ray.h"

class Camera {

public:
  // Constructor / Destructor
  Camera() {}
  virtual ~Camera() {}

  // Camera functions
  virtual Ray castRay(float x, float y) const = 0;

};

#endif
