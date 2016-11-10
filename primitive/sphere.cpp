#include "primitive/sphere.h"
#include "common/ray.h"


// Constructor /////////////////////////////////////////////////////////////////

Sphere::Sphere(Shader * shader)
  : Primitive(shader), radius_(0.5f) {}

Sphere::Sphere(Vector3d const& center, float radius, Shader * shader)
  : Primitive(shader), center_(center), radius_(radius) {}


// Primitive functions /////////////////////////////////////////////////////////

bool Sphere::intersect(Ray * ray) const {
 /*
  * IMPLEMENT ME!
  *
  * Our raytracer will iterate over all primitives in the scene.
  * This function tests whether a given ray intersects this primitive.
  * If the ray intersects this primitive, and if this primitive is closest to
  * the origin of the ray, then we need to save that information to the ray.
  *
  * First, determine whether the ray intersects this object. Next, calculate
  * the minimum distance from the ray's origin to the primitive's surface.
  * If this distance is shorter than the ray's length, than this is the
  * closest primitive to the camera (so far).
  *
  * Save that information to the ray by using:
  *
  *  ray->length = distance;  // The new (shorter) length of the ray
  *  ray->primitive = this;   // The primitive that is hit by the ray
  *
  * Also return true/false, whether the primitive was hit or not respectively.
  *
  */
  //calculate parameters for intersection
  float A = pow(ray->direction.x,2) + pow(ray->direction.y,2) + pow(ray->direction.z,2);
  float B = 2*((ray->direction.x)*(ray->origin.x) + (ray->direction.y)*(ray->origin.y) + (ray->direction.z)*(ray->origin.z)) ;
  float C = pow(ray->origin.x,2) + pow(ray->origin.y,2) + pow(ray->origin.z,2) + pow(radius_,2);
  float discriminant = pow(B,2) - 4*A*C;
  Vector3d distance_vector(0,0,0);
  //check whether ray hits the target
  if(discriminant < 0.0){
      return false;
      //ray doesn't intersect
  } else {
      float t1 = (-B + sqrt(discriminant))/(2*A);
      float t2 = (-B - sqrt(discriminant))/(2*A);
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
      if (ray->length > length(distance_Vector)){
          ray->length = length(distance_Vector);
          ray->primitive = this;
      }
  }
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
