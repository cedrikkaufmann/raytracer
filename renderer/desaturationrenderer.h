#ifndef DESATURATIONRENDERER_H
#define DESATURATIONRENDERER_H

#include "renderer/renderer.h"

class DesaturationRenderer : public Renderer {

public:
  // Constructor / Destructor
  DesaturationRenderer() : intensity_(1) {}
  virtual ~DesaturationRenderer() {}

  // Get
  float intensity() { return this->intensity_; }

  // Set
  void setIntensity(float intensity) { this->intensity_ = intensity; }

  // Render functions
  virtual Texture renderImage(Scene const& scene,
                              Camera const& camera,
                              int width, int height);

private:
  float intensity_;

};

#endif
