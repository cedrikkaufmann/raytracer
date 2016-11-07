#include "scene/simplescene.h"
#include "primitive/primitive.h"
#include "shader/shader.h"

bool SimpleScene::findIntersection(Ray * ray) const {
  bool hit = false;
  for (unsigned int i = 0; i < this->primitives_.size(); ++i)
    hit |= this->primitives_[i]->intersect(ray);
  return hit;
}

bool SimpleScene::findOcclusion(Ray * ray) const {
  for (unsigned int i = 0; i < this->primitives_.size(); ++i)
    if (this->primitives_[i]->intersect(ray)
        && !this->primitives_[i]->shader()->isTransparent())
      return true;
  return false;
}
