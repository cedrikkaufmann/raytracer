#ifndef BACKGROUNDRENDERER_H
#define BACKGROUNDRENDERER_H

#include "renderer/renderer.h"

class BackgroundRenderer : public Renderer {

public:
  // Constructor / Destructor
  BackgroundRenderer() {}
  virtual ~BackgroundRenderer() {}

  // Render functions
  virtual Texture renderImage(Scene const& scene,
                              Camera const& camera,
                              int width, int height);

};

#endif
