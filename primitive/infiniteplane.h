#ifndef INFINITEPLANE_H
#define INFINITEPLANE_H

#include "primitive/primitive.h"

class InfinitePlane : public Primitive {

public:
  // Constructor
  InfinitePlane(Shader * shader = nullptr);
  InfinitePlane(Vector3d const& origin, Vector3d const& normal, Shader * shader = nullptr);

  // Get
  Vector3d origin() const { return this->origin_; }
  Vector3d normal() const { return this->normal_; }

  // Set
  void setOrigin(Vector3d const& origin) { this->origin_ = origin; }
  void setNormal(Vector3d const& normal) { this->normal_ = normal; }

  // Primitive functions
  virtual bool intersect(Ray * ray) const;
  virtual Vector3d normalFromRay(Ray const& ray) const;

  // Bounding box
  virtual float minimumBounds(int dimension) const;
  virtual float maximumBounds(int dimension) const;

protected:
  Vector3d origin_, normal_;

};

#endif
