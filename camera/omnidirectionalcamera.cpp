#include "camera/omnidirectionalcamera.h"

Ray OmnidirectionalCamera::castRay(float x, float y) const {

    // Calculate the focus

    float phi = 2 * PI * x;
    float theta = 1 * PI * y;

    float r = 1;
    float x_1 = r * sin(theta) * cos(phi);
    float y_1 = r * sin(theta) * sin(phi);
    float z_1 = r * cos(theta);


    // Create a ray
    Ray ray;
    ray.origin = this->position_;
    ray.direction = Vector3d(x_1,y_1,z_1);
    normalize(&ray.direction);
    return ray;
}
