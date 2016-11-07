#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "common/boundingbox.h"
#include "common/ray.h"
#include "shader/shader.h"

class Primitive {

public:
  // Constructor / Destructor
  Primitive(Shader * shader = nullptr) : shader_(shader) {}
  virtual ~Primitive() {}

  // Get
  Shader * shader() const { return shader_; }

  // Set
  void setShader(Shader * shader) { shader_ = shader; }

  // Primitive functions
  virtual bool intersect(Ray * ray) const = 0;
  virtual Vector3d normalFromRay(Ray const& ray) const = 0;
  virtual Vector2d uvFromRay(Ray const& ray) const { return ray.surfacePosition; }

  // Bounding box
  virtual float minimumBounds(int dimension) const = 0;
  virtual float maximumBounds(int dimension) const = 0;
  BoundingBox boundingBox() const {
    return BoundingBox(Vector3d(this->minimumBounds(Vector3d::X),
                                this->minimumBounds(Vector3d::Y),
                                this->minimumBounds(Vector3d::Z)),
                       Vector3d(this->maximumBounds(Vector3d::X),
                                this->maximumBounds(Vector3d::Y),
                                this->maximumBounds(Vector3d::Z)));
  }

private:
  Shader * shader_;

};

#endif
