#ifndef SPHERE_H
#define SPHERE_H

#include "primitive/primitive.h"

class Sphere : public Primitive {

public:
  // Constructor
  Sphere(Shader * shader = nullptr);
  Sphere(Vector3d const& center, float radius, Shader * shader = nullptr);

  // Get
  Vector3d center() const { return this->center_; }
  float radius() const { return this->radius_; }

  // Set
  void setCenter(Vector3d const& center) { this->center_ = center; }
  void setRadius(float radius) { this->radius_ = radius; }

  // Primitive functions
  virtual bool intersect(Ray * ray) const;
  virtual Vector3d normalFromRay(Ray const& ray) const;

  // Bounding box
  virtual float minimumBounds(int dimension) const;
  virtual float maximumBounds(int dimension) const;

protected:
  Vector3d center_;
  float radius_;

};

#endif
