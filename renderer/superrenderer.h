#ifndef SUPERRENDERER_H
#define SUPERRENDERER_H

#include "renderer/renderer.h"

class SuperRenderer : public Renderer {

public:
  // Constructor / Destructor
  SuperRenderer() {}
  virtual ~SuperRenderer() {}

  // Get
  int superSamplingFactor() { return this->superSamplingFactor_; }

  // Set
  void setSuperSamplingFactor(int factor) { this->superSamplingFactor_ = factor; }

  // Render functions
  virtual Texture renderImage(Scene const& scene,
                              Camera const& camera,
                              int width, int height);


private:
  int superSamplingFactor_;

};

#endif
