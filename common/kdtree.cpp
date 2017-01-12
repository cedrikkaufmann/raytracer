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
    if(child[0] == nullptr && child[1] == nullptr) {// Blatt
        for(unsigned int i = 0; i < primitives->size(); i++) {
            primitives->at(i)->intersect(ray);
        }
        return (ray->primitive != 0 && ray->length < t1); //?
    }
  // ... otherwise we continue through the branches
    else {
        float d = (split - ray->origin[dimension])/ray->direction[dimension];

        int vor = 0;
        int zurueck = 1;

        if(ray->direction[dimension] < 0) {
            vor = 1;
            zurueck = 0;
        }

        if( d <= t0) { // d ist kleiner, gehe zurück
            return child[zurueck]->traverse(ray, t0, t1);
        } else if( d >= t1) { // d ist größer, gehe vor
            return child[vor]->traverse(ray,t0,t1);
        } else { // d ist gleich, gehe vor oder zurück, zuerst vor.
            return child[vor]->traverse(ray,t0,d) || child[zurueck]->traverse(ray,d,t1);
        }
    }
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

  if (depth % 2 == 0) {
      float median = 0;
      node->dimension = Vector3d::Z;

      for (unsigned int i = 0; i < primitives.size(); ++i) {
        median += primitives[i]->boundingBox().minimumCorner.z;
      }

      median = median / primitives.size();

      splitCornerA = Vector3d(boundingBox.maximumCorner.x, boundingBox.maximumCorner.y, median);
      splitCornerB = Vector3d(boundingBox.minimumCorner.x, boundingBox.minimumCorner.y, median);

      node->split = median;
  } else {
      float median = 0;
      node->dimension = Vector3d::Y;

      for (unsigned int i = 0; i < primitives.size(); ++i) {
        median += primitives[i]->boundingBox().minimumCorner.y;
      }

      median = median / primitives.size();

      splitCornerA = Vector3d(boundingBox.maximumCorner.x, median, boundingBox.maximumCorner.z);
      splitCornerB = Vector3d(boundingBox.minimumCorner.x, median, boundingBox.minimumCorner.z);

      node->split = median;
  }

  BoundingBox leftBox(boundingBox.minimumCorner, splitCornerA);
  BoundingBox rightBox(splitCornerB, boundingBox.maximumCorner);

  // Divide primitives into the left and right lists
  // Remember: A primitive can be in both lists!
  // Also remember: You split exactly at the minimum of a primitive,
  // make sure that primitive does *not* appear in both lists!
  for (unsigned int i = 0; i < primitives.size(); ++i) {
    BoundingBox boundingPrimitive = primitives[i]->boundingBox();

    if (node->dimension == Vector3d::Z) {
        if (boundingPrimitive.maximumCorner.z <= node->split || boundingPrimitive.minimumCorner.z < node->split) {
            leftPrimitives.push_back(primitives[i]);
        }

        if (boundingPrimitive.minimumCorner.z >= node->split) {
            rightPrimitives.push_back(primitives[i]);
        }
    } else{
        if (boundingPrimitive.maximumCorner.y <= node->split || boundingPrimitive.minimumCorner.y < node->split) {
            leftPrimitives.push_back(primitives[i]);
        }

        if (boundingPrimitive.minimumCorner.y >= node->split) {
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
