#ifndef SUPERRENDERER_H
#define SUPERRENDERER_H

#define MULTIPLE_RAYS 5

#include "renderer/renderer.h"

class SuperRenderer : public Renderer {

public:
  // Constructor / Destructor
  SuperRenderer() : superSamplingFactor_(4) {}
  virtual ~SuperRenderer() {}

  // Get
  float superSamplingFactor() { return this->superSamplingFactor_; }

  // Set
  void setSuperSamplingFactor(int const& factor) { this->superSamplingFactor_ = factor; }

  // Render functions
  virtual Texture renderImage(Scene const& scene,
                              Camera const& camera,
                              int width, int height);


private:
  float superSamplingFactor_;
};

#endif // SUPERRENDERER_H
