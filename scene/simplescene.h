#ifndef SIMPLESCENE_H
#define SIMPLESCENE_H

#include "scene/scene.h"

class SimpleScene : public Scene {

public:
  // Raytracing functions
  virtual bool findIntersection(Ray * ray) const;
  virtual bool findOcclusion(Ray * ray) const;

};

#endif
