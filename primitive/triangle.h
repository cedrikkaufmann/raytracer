#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "primitive/primitive.h"

class Triangle : public Primitive {

public:
  // Constructor
  Triangle(Shader * shader = nullptr);
  Triangle(Vector3d const& a, Vector3d const& b, Vector3d const& c, Shader * shader = nullptr);

  // Get
  Vector3d vertex(int index) const { return this->vertex_[index]; }

  // Set
  void setVertex(int index, Vector3d const& vertex) { this->vertex_[index] = vertex; }

  // Primitive functions
  virtual bool intersect(Ray * ray) const;
  virtual Vector3d normalFromRay(Ray const& ray) const;

  // Bounding box
  virtual float minimumBounds(int dimension) const;
  virtual float maximumBounds(int dimension) const;

protected:
  Vector3d vertex_[3];

};

#endif
