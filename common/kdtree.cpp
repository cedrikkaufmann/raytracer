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

  // Determine the bounding box of the entire kD-Tree
  for (unsigned int i = 0; i < primitives.size(); ++i) {
    this->bounds.minimumCorner.x = std::min(this->bounds.minimumCorner.x, primitives[i]->boundingBox().minimumCorner.x);
    this->bounds.minimumCorner.y = std::min(this->bounds.minimumCorner.y, primitives[i]->boundingBox().minimumCorner.y);
    this->bounds.minimumCorner.z = std::min(this->bounds.minimumCorner.z, primitives[i]->boundingBox().minimumCorner.z);
    this->bounds.maximumCorner.x = std::max(this->bounds.maximumCorner.x, primitives[i]->boundingBox().maximumCorner.x);
    this->bounds.maximumCorner.y = std::max(this->bounds.maximumCorner.y, primitives[i]->boundingBox().maximumCorner.y);
    this->bounds.maximumCorner.z = std::max(this->bounds.maximumCorner.z, primitives[i]->boundingBox().maximumCorner.z);
  }

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
  Vector3d vecDiameter = boundingBox.maximumCorner - boundingBox.minimumCorner;

  // Test whether we have reached a leaf node...
    //printf("(kDTree): Added leave node with %zu primitives.\n", primitives.size());


  // ... otherwise create a new inner node by splitting through the widest dimension
  // ...

  Node *node = new Node();

  if (depth == maximumDepth || primitives.size() < minimumNumberOfPrimitives) {
      printf("(kDTree): Added leave node with %zu primitives.\n", primitives.size());

      for (unsigned int i = 0; i < primitives.size(); ++i) {
        //segfault:11 occurs by adding primitives to leaf vector
        node->primitives->push_back(primitives[i]);
      }

      return node;
  }

  // New bounding boxes and primitive lists
  std::vector<Primitive*> leftPrimitives, rightPrimitives;

  // Determine the split position
  // Note: Use the median of the minimum bounds of the primitives

  // Set the left and right bounding boxes
  Vector3d splitCornerA, splitCornerB;
  float medianY = 0, medianZ = 0;

  if (depth % 2 == 0) {
      node->dimension = Vector3d::Z;
      node->split = medianZ;

      for (unsigned int i = 0; i < primitives.size(); ++i) {
        medianZ += primitives[i]->boundingBox().minimumCorner.z;
      }

      medianZ = medianZ / primitives.size();

      splitCornerA = Vector3d(boundingBox.maximumCorner.x, boundingBox.maximumCorner.y, medianZ);
      splitCornerB = Vector3d(boundingBox.minimumCorner.x, boundingBox.minimumCorner.y, medianZ);
  } else {
      node->dimension = Vector3d::Y;
      node->split = medianY;

      for (unsigned int i = 0; i < primitives.size(); ++i) {
        medianY += primitives[i]->boundingBox().minimumCorner.y;
      }

      medianY = medianY / primitives.size();

      splitCornerA = Vector3d(boundingBox.maximumCorner.x, medianY, boundingBox.maximumCorner.z);
      splitCornerB = Vector3d(boundingBox.minimumCorner.x, medianY, boundingBox.minimumCorner.z);
  }

  BoundingBox leftBox(boundingBox.minimumCorner, splitCornerA);
  BoundingBox rightBox(splitCornerB, boundingBox.maximumCorner);

  // Divide primitives into the left and right lists
  // Remember: A primitive can be in both lists!
  // Also remember: You split exactly at the minimum of a primitive,
  // make sure that primitive does *not* appear in both lists!
  for (unsigned int i = 0; i < primitives.size(); ++i) {
    BoundingBox boundingPrimitive = primitives[i]->boundingBox();

    if (depth % 2 == 0) {
        if (boundingPrimitive.maximumCorner.z <= medianZ || boundingPrimitive.minimumCorner.z < medianZ) {
            leftPrimitives.push_back(primitives[i]);
        }

        if (boundingPrimitive.minimumCorner.z >= medianZ) {
            rightPrimitives.push_back(primitives[i]);
        }
    } else {
        if (boundingPrimitive.maximumCorner.y <= medianY || boundingPrimitive.minimumCorner.y < medianY) {
            leftPrimitives.push_back(primitives[i]);
        }

        if (boundingPrimitive.minimumCorner.y >= medianY) {
            rightPrimitives.push_back(primitives[i]);
        }
    }
  }

  printf("(kDTree): Split %zu -> %zu | %zu\n", primitives.size(), leftPrimitives.size(), rightPrimitives.size());

  // Recursively build the tree
  depth++;
  node->child[0] = build(leftBox, leftPrimitives, depth);
  node->child[1] = build(rightBox, rightPrimitives, depth);

  return node;
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
