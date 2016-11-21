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
  // Implement me!
  // Use Triangle::uvFromRay to get the UV coordinates.
  return Vector3d();
}
