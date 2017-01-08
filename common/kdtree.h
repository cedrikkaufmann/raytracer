#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include "primitive/primitive.h"

// Forward declaration
class Node;

class KdTree {

public:
  // Constructor / Destructor
  KdTree(std::vector<Primitive *> const& primitives,
         int maximumDepth = 16,
         int minimumNumberOfPrimitives = 4);
  virtual ~KdTree();

  bool intersect(Ray * ray) const;

protected:
  Node * build(BoundingBox const& boundingBox,
               std::vector<Primitive*> const& primitives, int depth);

private:
  Node * root;
  int maximumDepth;
  int minimumNumberOfPrimitives;
  BoundingBox bounds;

};

#endif
