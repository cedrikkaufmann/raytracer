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
  return Ray();
}
