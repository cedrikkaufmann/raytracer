#ifndef TEXTUREDTRIANGLE_H
#define TEXTUREDTRIANGLE_H

#include "primitive/smoothtriangle.h"

class TexturedTriangle : public SmoothTriangle {

public:
  TexturedTriangle(Shader * shader = nullptr);
  TexturedTriangle(Vector3d const& a, Vector3d const& b, Vector3d const& c,
                   Vector3d const& na, Vector3d const& nb, Vector3d const& nc,
                   Vector2d const& ta, Vector2d const& tb, Vector2d const& tc,
                   Shader * shader = nullptr);

  // Get
  Vector2d textureCoordinates(int index) const { return this->textureCoordinates_[index]; }

  // Set
  void setTextureCoordinates(int index, Vector2d const& textureCoordinates) { this->textureCoordinates_[index] = textureCoordinates; }

  // Primitive functions
  virtual Vector2d uvFromRay(Ray const& ray) const;

protected:
  Vector2d textureCoordinates_[3];

};

#endif
