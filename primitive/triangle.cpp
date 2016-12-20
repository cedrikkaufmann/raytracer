#include <algorithm>
#include "primitive/triangle.h"


// Constructor /////////////////////////////////////////////////////////////////

Triangle::Triangle(Shader * shader)
  : Primitive(shader) {}

Triangle::Triangle(Vector3d const& a, Vector3d const& b, Vector3d const& c, Shader * shader)
  : Primitive(shader), vertex_{a,b,c} {}


// Primitive functions /////////////////////////////////////////////////////////

bool Triangle::intersect(Ray * ray) const {
  // We use the Möller–Trumbore intersection algorithm

  // Determine two neighboring edge vectors
  Vector3d const edge1 = this->vertex_[1] - this->vertex_[0];
  Vector3d const edge2 = this->vertex_[2] - this->vertex_[0];

  // Begin calculating determinant
  Vector3d const pVec = crossProduct(ray->direction, edge2);

  // Make sure the ray is not parallel to the triangle
  float const det = dotProduct(edge1, pVec);
  if (fabs(det) < EPSILON)
    return false;
  float const inv_det = 1.0f / det;

  // Calculate u and test bound
  Vector3d const tVec = ray->origin - this->vertex_[0];
  float const u = dotProduct(tVec, pVec)*inv_det;
  // Test whether the intersection lies outside the triangle
  if (0.0f > u || u > 1.0f)
    return false;

  // Calculate v and test bound
  Vector3d const qVec = crossProduct(tVec, edge1);
  float const v = dotProduct(ray->direction, qVec)*inv_det;
  // Test whether the intersection lies outside the triangle
  if (0.0f > v || u+v > 1.0f)
    return false;

  // Test whether this is the foremost primitive in front of the camera
  float const t = dotProduct(edge2, qVec)*inv_det;
  if (t < EPSILON || ray->length < t)
    return false;

  // Prepare the ray
  ray->length = t;
  ray->primitive = this;
  ray->surfacePosition = Vector2d(u,v);
  return true;
}

Vector3d Triangle::normalFromRay(Ray const& ray) const {
    Vector3d const edge1 = this->vertex_[1] - this->vertex_[0];
     Vector3d const edge2 = this->vertex_[2] - this->vertex_[0];
     Vector3d const normal = normalized(crossProduct(edge1, edge2));
     // Make sure the normal works for both sides of the triangle
     return (dotProduct(normal, ray.direction) < 0 ? normal : -normal);
}


// Bounding box ////////////////////////////////////////////////////////////////

float Triangle::minimumBounds(int dimension) const {
  return std::min(this->vertex_[0][dimension],
      std::min(this->vertex_[1][dimension], this->vertex_[2][dimension]));
}

float Triangle::maximumBounds(int dimension) const {
  return std::max(this->vertex_[0][dimension],
      std::max(this->vertex_[1][dimension], this->vertex_[2][dimension]));
}

