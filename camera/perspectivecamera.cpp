#include "camera/perspectivecamera.h"

PerspectiveCamera::PerspectiveCamera()
  : forwardDirection_(0,0,-1), upDirection_(0,1,0), fovAngle_(70) {}

Ray PerspectiveCamera::castRay(float x, float y) const {
 /*
  * IMPLEMENT ME!
  *
  * Start by calculating and normalizing the axes of your camera coordinate system.
  * Next, calculate the focus.
  * Finally, create a new ray, and set its origin and direction.
  *
  */

  double window_h = tan(fovAngle_/2) * length(forwardDirection_);
  double window_w = window_h;

  double norm_x = x / window_h;
  double norm_y = y / window_w;

  Ray ray;
  ray.origin = position;
  Vector3d focus = forwardDirection_ * length(forwardDirection_);

  ray.direction = Vector3d(norm_x, norm_y, INFINITY)


  return Ray();
}
