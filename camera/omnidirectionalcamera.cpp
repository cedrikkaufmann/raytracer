#include "camera/omnidirectionalcamera.h"

Ray OmnidirectionalCamera::castRay(float x, float y) const {
    // Simply calculate angle
    float const phi = 2 * PI * x;
    float const theta = PI * y;

    // Simply calculate cartesian coordinates from previous calculated angles
    float const u = sin(theta) * cos(phi);
    float const v = sin(theta) * sin(phi);
    float const z = cos(theta);

    // Create a ray
    Ray ray;
    ray.origin = this->position_;
    ray.direction = Vector3d(u, v, z);
    normalize(&ray.direction);
    return ray;

  return Ray();
}
