#include "primitive/smoothtriangle.h"


// Constructor /////////////////////////////////////////////////////////////////

SmoothTriangle::SmoothTriangle(Shader * shader)
  : Triangle(shader) {}

SmoothTriangle::SmoothTriangle(Vector3d const& a, Vector3d const& b, Vector3d const& c,
                               Vector3d const& na, Vector3d const& nb, Vector3d const& nc,
                               Shader * shader)
  : Triangle(a,b,c,shader), normal_{na,nb,nc} {}


// Primitive functions /////////////////////////////////////////////////////////

Vector3d SmoothTriangle::normalFromRay(Ray const& ray) const {
  // this->uvFromRay may be overloaded, e.g. by TexturedTriangle.
  // Use Triangle::surfacePositionFromRay to get the UV coordinates.
  Vector2d const surface = Triangle::uvFromRay(ray);
  return normalized(
        surface.u * normal_[1]
      + surface.v * normal_[2]
      + (1.0f - surface.u - surface.v) * normal_[0]);
}
