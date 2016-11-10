#include <algorithm>
#include "primitive/triangle.h"


// Constructor /////////////////////////////////////////////////////////////////

Triangle::Triangle(Shader * shader)
  : Primitive(shader) {}

Triangle::Triangle(Vector3d const& a, Vector3d const& b, Vector3d const& c, Shader * shader)
  : Primitive(shader), vertex_{a,b,c} {}


// Primitive functions /////////////////////////////////////////////////////////

bool Triangle::intersect(Ray * ray) const {
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
  // Span plane defined by vertices of triangle
  // Using a as base vector and edges between a,b and a,c
  Vector3d base = vertex_[0];
  Vector3d edge_b = vertex_[1] - vertex_[0];
  Vector3d edge_c = vertex_[2] - vertex_[0];

  // Calculating normal vector of plane
  Vector3d normal = crossProduct(edge_b, edge_c);
  normalize(&normal);

  // Calculation of intersection using hesse normal form
  float equation_denominator = dotProduct(ray->direction, normal);

  if (equation_denominator != 0.0) {
      float normal_distance = dotProduct(ray->direction, normal);
      float equation_numerator = normal_distance - dotProduct(ray->origin, normal);

      float intersection = equation_numerator / equation_denominator;

      if (intersection <= 0.0) {
          // Behind visible area, parallel or in plane
          return false;
      } else {
          // Intersection with plane, check if also with triangle

          // Calculate intersection
          Vector3d intersection_plane = ray->origin + normal_distance * normalized(ray->direction);
          Vector3d edge_a = intersection_plane - base;

          // Calculate barycentric coordinates
          float barycentric_denominator = dotProduct(edge_c, edge_c) * dotProduct(edge_b, edge_b) - dotProduct(edge_c, edge_b) * dotProduct(edge_b, edge_c);

          float barycentric_a = (dotProduct(edge_a, edge_b) * dotProduct(edge_c, edge_c) - dotProduct(edge_a, edge_c) * dotProduct(edge_c, edge_b))
                  / barycentric_denominator;
          float barycentric_b = (dotProduct(edge_a, edge_c) * dotProduct(edge_b, edge_b) - dotProduct(edge_a, edge_b) * dotProduct(edge_b, edge_c))
                  / barycentric_denominator;

          // Use Barycentric Coordinates to determine intersection
          if ((barycentric_a < 0) || (barycentric_a > 1)) {
              return false;
          } else if (barycentric_b < 0) {
              return false;
          } else if ((barycentric_a + barycentric_b) > 1) {
              return false;
          } else {             
              if (ray->length > normal_distance) {
                  ray->length = normal_distance;
                  ray->primitive = this;
              }
               printf("Intersection with triangle detected");
              return true;
          }
      }
  } else {
      // No solution divide by zero
      return false;
  }
}

Vector3d Triangle::normalFromRay(Ray const& ray) const {
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

float Triangle::minimumBounds(int dimension) const {
 /*
  * IMPLEMENT ME!
  *
  * These values are used for determining the bounding box.
  * This should return the minimum value along the given dimension.
  *
  */
  return -INFINITY;
}

float Triangle::maximumBounds(int dimension) const {
 /*
  * IMPLEMENT ME!
  *
  * These values are used for determining the bounding box.
  * This should return the maximum value along the given dimension.
  *
  */
  return +INFINITY;
}
