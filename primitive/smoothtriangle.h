#ifndef SMOOTHTRIANGLE_H
#define SMOOTHTRIANGLE_H

#include "primitive/triangle.h"

class SmoothTriangle : public Triangle {

public:
  SmoothTriangle(Shader * shader = nullptr);
  SmoothTriangle(Vector3d const& a, Vector3d const& b, Vector3d const& c,
                 Vector3d const& na, Vector3d const& nb, Vector3d const& nc,
                 Shader * shader = nullptr);

  // Get
  Vector3d normal(int index) const { return this->normal_[index]; }

  // Set
  void setNormal(int index, Vector3d const& normal) { this->normal_[index] = normalized(normal); }

  // Primitive functions
  virtual Vector3d normalFromRay(Ray const& ray) const;

protected:
  Vector3d normal_[3];

};

#endif
