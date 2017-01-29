#include "camera/perspectivecamera.h"
#include <iostream>

PerspectiveCamera::PerspectiveCamera()
  : forwardDirection_(0,0,-1), upDirection_(0,1,0), fovAngle_(70) {}

Ray PerspectiveCamera::castRay(float x, float y) const {
  // Set up the coordinate system
  Vector3d const zAxis = normalized(this->forwardDirection_);
  Vector3d const xAxis = normalized(crossProduct(zAxis, this->upDirection_));
  Vector3d const yAxis = normalized(crossProduct(xAxis, zAxis));

  // Calculate the focus
  float const focus = 1.0 / std::tan((this->fovAngle_*PI/180) / 2);

  // Create a ray
  Ray ray;
  ray.origin = this->position_;
  ray.direction = x*xAxis + y*yAxis + focus*zAxis;
  normalize(&ray.direction);
  return ray;
}
