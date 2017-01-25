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

  // If this is a leaf node, we intersect with all the primitives...
  if (primitives) {

    bool hit = false;
    for (unsigned int i = 0; i < this->primitives->size(); ++i)
      hit |= (*this->primitives)[i]->intersect(ray);
    return hit;

  } else { // ... otherwise we continue through the branches

    // Determine the order in which we intersect the child nodes
    float const d = (this->split - ray->origin[this->dimension])
        / ray->direction[this->dimension];
    int front = ray->direction[this->dimension] < 0 ? 1 : 0;
    int back = 1 - front;

    if (d <= t0) {
      // t0..t1 is totally behind d, only go through the back node.
      return this->child[back]->traverse(ray, t0, t1);
    } else if (d >= t1) {
      // t0..t1 is totally in front of d, only go to front node.
      return this->child[front]->traverse(ray, t0, t1);
    } else {
      // Traverse both children. Front node first, back node last.
      if (this->child[front]->traverse(ray, t0, d))
        return true;
      else
        return this->child[back]->traverse(ray, d, t1);
    }
  }

}

KdTree::KdTree(std::vector<Primitive*> const& primitives,
               int maximumDepth,
               int minimumNumberOfPrimitives)
  : maximumDepth(maximumDepth),
    minimumNumberOfPrimitives(minimumNumberOfPrimitives),
    bounds(Vector3d(1,1,1)*INFINITY, Vector3d(1,1,1)*-INFINITY) {

  // Adjust the bounding box of the entire kD-Tree
  for (unsigned int i = 0; i < primitives.size(); ++i) {
    for (int d = 0; d < 3; ++d) {
      this->bounds.minimumCorner[d] = std::min(this->bounds.minimumCorner[d], primitives[i]->minimumBounds(d));
      this->bounds.maximumCorner[d] = std::max(this->bounds.maximumCorner[d], primitives[i]->maximumBounds(d));
    }
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

  // Determine the diameter of the bounding box
  Vector3d const diameter = boundingBox.maximumCorner-boundingBox.minimumCorner;

  // Test whether we have reached a leaf node...
  int minimumDimension = ((diameter.x < diameter.y)
                          ? ((diameter.x < diameter.z) ? 0 : 2)
                          : ((diameter.y < diameter.z) ? 1 : 2));
  if (depth >= this->maximumDepth
      || (int) primitives.size() <= this->minimumNumberOfPrimitives
      || (diameter[minimumDimension]) <= EPSILON) {
    Node * leafNode = new Node();
    leafNode->primitives = new std::vector<Primitive*>(primitives);
    //printf("(kDTree): Added leave node with %zu primitives.\n", primitives.size());
    return leafNode;
  }

  // ... otherwise create a new inner node by splitting through the widest dimension
  Node * node = new Node();
  node->dimension = ((diameter.x > diameter.y)
                     ? ((diameter.x > diameter.z) ? 0 : 2)
                     : ((diameter.y > diameter.z) ? 1 : 2));

  // New bounding boxes and primitive lists
  BoundingBox leftBox(boundingBox);
  BoundingBox rightBox(boundingBox);
  std::vector<Primitive*> leftPrimitives, rightPrimitives;

  // Determine the split position
  // Note: Use the median of the minimum bounds of the primitives
  std::vector<float> minimumValues;
  for (unsigned int i = 0; i < primitives.size(); ++i)
    minimumValues.push_back(primitives[i]->minimumBounds(node->dimension));
  std::sort(minimumValues.begin(), minimumValues.end());
  node->split = minimumValues[minimumValues.size()/2];

  // Set the left and right bounding boxes
  leftBox.maximumCorner[node->dimension] = node->split;
  rightBox.minimumCorner[node->dimension] = node->split;

  // Divide primitives into the left and right lists
  // Remember: A primitive can be in both lists!
  // Also remember: You split exactly at the minimum of a primitive,
  // make sure that primitive does *not* appear in both lists!
  for (unsigned int i = 0; i < primitives.size(); ++i) {
    if (primitives[i]->minimumBounds(node->dimension) < node->split)
      leftPrimitives.push_back(primitives[i]);
    if (primitives[i]->maximumBounds(node->dimension) >=  node->split)
      rightPrimitives.push_back(primitives[i]);
  }

  //printf("(kDTree): Split %zu -> %zu | %zu\n", primitives.size(), leftPrimitives.size(), rightPrimitives.size());

  // Recursively build the tree
  node->child[0] = this->build(leftBox, leftPrimitives, ++depth);
  node->child[1] = this->build(rightBox, rightPrimitives, ++depth);
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
  if (tMax-tMin > EPSILON)
    return this->root->traverse(ray, tMin, tMax);
  else
    return false;
}
