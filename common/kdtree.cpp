#include "kdtree.h"
#include "common/ray.h"

#include <iostream>
#include <algorithm>

// Definition of a node
struct Node {

  // Constructor / Destructor
  Node() : dimension(0), split(0) {
    child[0] = nullptr;
    child[1] = nullptr;
    primitives = nullptr;
  }
  virtual ~Node() {
    delete child[0];
    delete child[1];
    delete primitives;
  }

  // Traversal function
  bool traverse(Ray * ray, float t0, float t1) const;

  // Branch split
  Node * child[2];
  int dimension;
  float split;

  // Leaf primitives
  std::vector<Primitive*> * primitives;

};


bool Node::traverse(Ray * ray, float t0, float t1) const {
  // Implement me!

  // If this is a leaf node, we intersect with all the primitives...

  // ... otherwise we continue through the branches

  // Determine the order in which we intersect the child nodes

  // Traverse the tree and return whether a primitive was hit or not.
  // Make sure you only traverse those children that are intersected by the ray
  return false;
}

KdTree::KdTree(std::vector<Primitive*> const& primitives,
               int maximumDepth,
               int minimumNumberOfPrimitives)
  : maximumDepth(maximumDepth),
    minimumNumberOfPrimitives(minimumNumberOfPrimitives),
    bounds(Vector3d(1,1,1)*INFINITY, -Vector3d(1,1,1)*INFINITY) {

  // Implement me!
  // Determine the bounding box of the entire kD-Tree

  // Recursively build the kD-Tree
  root = this->build(this->bounds, primitives, 0);
  printf("(kDTree): %zu primitives organized into tree\n", primitives.size());
}

KdTree::~KdTree() {
  // Clean up the tree recursively
  delete this->root;
}

Node * KdTree::build(BoundingBox const& boundingBox,
                     std::vector<Primitive*> const& primitives, int depth) {

  // Implement me!

  // Determine the diameter of the bounding box

  // Test whether we have reached a leaf node...
    //printf("(kDTree): Added leave node with %zu primitives.\n", primitives.size());


  // ... otherwise create a new inner node by splitting through the widest dimension
  // ...

  // New bounding boxes and primitive lists

  // Determine the split position
  // Note: Use the median of the minimum bounds of the primitives

  // Set the left and right bounding boxes

  // Divide primitives into the left and right lists
  // Remember: A primitive can be in both lists!
  // Also remember: You split exactly at the minimum of a primitive,
  // make sure that primitive does *not* appear in both lists!

  //printf("(kDTree): Split %zu -> %zu | %zu\n", primitives.size(), leftPrimitives.size(), rightPrimitives.size());

  // Recursively build the tree

  //return node;

  //Remove this when you are done
  return nullptr;
}

bool KdTree::intersect(Ray * ray) const {
  // Determine the intersection range
  Vector3d const minTemp = componentQuotient(this->bounds.minimumCorner - ray->origin, ray->direction);
  Vector3d const maxTemp = componentQuotient(this->bounds.maximumCorner - ray->origin, ray->direction);
  float const tMin = std::max(std::max(std::min(minTemp.x, maxTemp.x),
                                       std::min(minTemp.y, maxTemp.y)),
                              std::min(minTemp.z, maxTemp.z));
  float const tMax = std::min(std::min(std::max(minTemp.x, maxTemp.x),
                                       std::max(minTemp.y, maxTemp.y)),
                              std::max(minTemp.z, maxTemp.z));

  // Traverse the tree recursively
  if (this->root && tMax-tMin > EPSILON)
    return this->root->traverse(ray, tMin, tMax);
  else
    return false;
}
