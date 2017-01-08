#ifndef SIMPLERENDERER_H
#define SIMPLERENDERER_H

#include "renderer/renderer.h"

class SimpleRenderer : public Renderer {

public:
  // Constructor / Destructor
  SimpleRenderer() {}
  virtual ~SimpleRenderer() {}

  // Render functions
  virtual Texture renderImage(Scene const& scene,
                              Camera const& camera,
                              int width, int height);

};

#endif
