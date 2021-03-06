#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <vector>
#include "primitive/primitive.h"

// Forward declarations
class KdTree;

class ObjModel : public Primitive {

public:
  enum ObjStyle {
    NONORMALS,
    NORMALS,
    TEXTURENORMALS
  };
  enum TriangleStyle {
    SMOOTH,
    STANDARD,
    TEXTURED
  };

  // Constructor
  ObjModel(Shader * shader = nullptr);
  virtual ~ObjModel();

  // Load object data
  bool loadObj(char const* fileName,
               Vector3d const& scale = Vector3d(1,1,1),
               Vector3d const& translation = Vector3d(0,0,0),
               ObjStyle objStyle = NONORMALS,
               TriangleStyle triangleStyle = STANDARD);

  // Primitive functions
  virtual bool intersect(Ray * ray) const;
  virtual Vector3d normalFromRay(Ray const& ray) const;

  // Bounding box
  virtual float minimumBounds(int dimension) const;
  virtual float maximumBounds(int dimension) const;

protected:
  Vector3d minBounds, maxBounds;
  std::vector<Primitive*> primitives;
  KdTree * tree;

};

#endif
