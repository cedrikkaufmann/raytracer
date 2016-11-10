#include "camera/perspectivecamera.h"

PerspectiveCamera::PerspectiveCamera()
  : forwardDirection_(0,0,-1), upDirection_(0,1,0), fovAngle_(70) {}

Ray PerspectiveCamera::castRay(float x, float y) const {
  Vector3d direction(x * -tan(fovAngle_/2 * M_PI/180),
                     y * tan(fovAngle_/2 * M_PI/180),
                     forwardDirection_.z);
  normalize(&direction);

  Ray ray;
  ray.origin = position_;
  ray.direction = direction;

  return ray;
}
