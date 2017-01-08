#include "camera/omnidirectionalcamera.h"

Ray OmnidirectionalCamera::castRay(float x, float y) const {
  // xy are uv coordinates, so we can directly determine the angles
  float const phi = y * PI;
  float const rho = x * 2*PI;

  // Calculate the direction
  Vector3d const direction(std::sin(phi)*std::cos(rho),
                           std::cos(phi),
                           std::sin(phi)*std::sin(rho));

  // Create a ray
  Ray ray;
  ray.origin = this->position_;
  ray.direction = direction;
  normalize(&ray.direction);
  return ray;
}
