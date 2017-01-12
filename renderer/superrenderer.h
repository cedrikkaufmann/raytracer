#ifndef SUPERRENDERER_H
#define SUPERRENDERER_H

#define MULTIPLE_RAYS 5

#include "renderer/renderer.h"

class SuperRenderer : public Renderer {

public:
  // Constructor / Destructor
  SuperRenderer() {}
  virtual ~SuperRenderer() {}

  // Render functions
  virtual Texture renderImage(Scene const& scene,
                              Camera const& camera,
                              int width, int height);

};

#endif // SUPERRENDERER_H
