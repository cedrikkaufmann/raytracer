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

    Vector3d a = vertex_[0], b = vertex_[1], c = vertex_[2];

    const Vector3d edge1 = b - a;
    const Vector3d edge2 = c - a;

    const Vector3d pvec = crossProduct(ray->direction , edge2);

    const float det = dotProduct(edge1, pvec);
    const float inv_det = 1.0f / det;

    const Vector3d tvec = ray->origin - a;
    float lambda = dotProduct(tvec, pvec);
    lambda *= inv_det;

    if (lambda < 0.0f || lambda > 1.0f) {
        return false;
    }

    const Vector3d qvec = crossProduct(tvec , edge1);
    float mue = dotProduct(ray->direction, qvec);
    mue *= inv_det;

    if (mue < 0.0f || mue + lambda > 1.0f) {
        return false;
    }

    float f = dotProduct(edge2, qvec);
    f *= inv_det;
    if (ray->length <= f) {
        return false;
    }

    ray->length = f;
    ray->primitive = this;

    return true;
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
