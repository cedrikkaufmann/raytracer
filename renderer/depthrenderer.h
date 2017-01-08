#ifndef DEPTHRENDERER_H
#define DEPTHRENDERER_H

#include "renderer/renderer.h"

class DepthRenderer : public Renderer {

public:
  // Constructor / Destructor
  DepthRenderer() {}
  virtual ~DepthRenderer() {}

  // Render functions
  virtual Texture renderImage(Scene const& scene,
                              Camera const& camera,
                              int width, int height);

};

#endif
