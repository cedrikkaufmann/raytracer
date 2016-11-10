#include "primitive/sphere.h"
#include "common/ray.h"


// Constructor /////////////////////////////////////////////////////////////////

Sphere::Sphere(Shader * shader)
  : Primitive(shader), radius_(0.5f) {}

Sphere::Sphere(Vector3d const& center, float radius, Shader * shader)
  : Primitive(shader), center_(center), radius_(radius) {}


// Primitive functions /////////////////////////////////////////////////////////

bool Sphere::intersect(Ray * ray) const {
  //calculate parameters for intersection
  Vector3d diff = ray->origin - center_;
  float a = dotProduct(ray->direction, ray->direction);
  float b = 2 * dotProduct(ray->direction, diff);
  float c = dotProduct(diff, diff) - radius_ * radius_;
  float discriminant = pow(b,2) - 4*a*c;

  if (discriminant < 0.0) {//ray doesn't intersect
    return false;
  }

  Vector3d distance_vector(0,0,0);
  float t1 = (-b + sqrt(discriminant))/(2*a);
  float t2 = (-b - sqrt(discriminant))/(2*a);
  //ray is tangent to sphere
  if(discriminant == 0.0) {
    //doesn't matter if t1 or t2 is used, they are the same
    distance_vector = ray->direction * t1;
  } else {
    //need to find closest point here
    if(t1 < t2) {
        distance_vector = ray->direction * t1;
    } else {
        distance_vector = ray->direction * t2;
    }
  }

  if (ray->length < length(distance_vector)){
    return false;
  }

  ray->length = length(distance_vector);
  ray->primitive = this;
  return true;
}

Vector3d Sphere::normalFromRay(Ray const& ray) const {
 /*
  * IMPLEMENT ME!
  *
  * This function should return the surface normal at the point that is
  * hit by the given ray.
  *
  */
  return Vector3d();
}


// Bounding box ////////////////////////////////////////////////////////////////

float Sphere::minimumBounds(int dimension) const {
 /*
  * IMPLEMENT ME!
  *
  * These values are used for determining the bounding box.
  * This should return the minimum value along the given dimension.
  *
  */
  return -INFINITY;
}

float Sphere::maximumBounds(int dimension) const {
 /*
  * IMPLEMENT ME!
  *
  * These values are used for determining the bounding box.
  * This should return the maximum value along the given dimension.
  *
  */
  return +INFINITY;
}
