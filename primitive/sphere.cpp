#include "primitive/sphere.h"
#include "common/ray.h"


// Constructor /////////////////////////////////////////////////////////////////

Sphere::Sphere(Shader * shader)
  : Primitive(shader), radius_(0.5f) {}

Sphere::Sphere(Vector3d const& center, float radius, Shader * shader)
  : Primitive(shader), center_(center), radius_(radius) {}


// Primitive functions /////////////////////////////////////////////////////////

bool Sphere::intersect(Ray * ray) const {
  // Use the definitions from the lecture
  Vector3d const difference = ray->origin - this->center_;
  float const a = dotProduct(ray->direction, ray->direction);
  float const b = 2.0f * dotProduct(ray->direction, difference);
  float const c = dotProduct(difference, difference) - this->radius_*this->radius_;
  float const discriminant = b*b - 4*a*c;

  // Test whether the ray could intersect at all
  if (discriminant < 0)
    return false;
  float const root = std::sqrt(discriminant);

  // Stable solution
  float const q = -0.5f*(b < 0 ? (b-root) : (b+root));
  float const t = c/q;

  // Test whether this is the foremost primitive in front of the camera
  if (t < EPSILON || ray->length < t)
    return false;

  // Prepare the ray
  ray->length = t;
  ray->primitive = this;

  // Determine the surface position
  Vector3d const normal = this->normalFromRay(*ray);
  float const phi = std::acos(normal.y);
  float const rho = std::atan2(normal.z, normal.x) + PI;
  ray->surfacePosition = Vector2d(rho/(2*PI), phi/PI);

  return true;
}

Vector3d Sphere::normalFromRay(Ray const& ray) const {
  Vector3d const target = ray.origin + ray.length*ray.direction;
  return normalized(target - this->center_);
}


// Bounding box ////////////////////////////////////////////////////////////////

float Sphere::minimumBounds(int dimension) const {
  return this->center_[dimension] - this->radius_;
}

float Sphere::maximumBounds(int dimension) const {
  return this->center_[dimension] + this->radius_;
}

