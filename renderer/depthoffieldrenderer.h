#ifndef DEPTHOFFIELDRENDERER_H
#define DEPTHOFFIELDRENDERER_H

#include "renderer/renderer.h"

class DepthOfFieldRenderer : public Renderer {

public:
  // Constructor / Destructor
  DepthOfFieldRenderer() {}
  virtual ~DepthOfFieldRenderer() {}

  // Get
  float apertureRadius() { return this->apertureRadius_; }
  int apertureRays() { return this->apertureRays_; }
  float focalDistance() { return this->focalDistance_; }

  // Set
  void setApertureRadius(float radius) { this->apertureRadius_ = radius; }
  void setApertureRays(int count) { this->apertureRays_ = count; }
  void setFocalDistance(float distance) { this->focalDistance_ = distance; }

  // Render functions
  virtual Texture renderImage(Scene const& scene,
                              Camera const& camera,
                              int width, int height);

private:
  float apertureRadius_;
  int apertureRays_;
  float focalDistance_;

};

#endif
