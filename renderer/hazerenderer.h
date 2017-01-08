#ifndef HAZERENDERER_H
#define HAZERENDERER_H

#include "renderer/renderer.h"

class HazeRenderer : public Renderer {

public:
  // Constructor / Destructor
  HazeRenderer() : falloff_(1), hazeColor_(1,1,1) {}
  virtual ~HazeRenderer() {}

  // Get
  Color hazeColor() { return this->hazeColor_; }
  float falloff() { return this->falloff_; }

  // Set
  void setHazeColor(Color const& color) { this->hazeColor_ = color; }
  void setFalloff(float falloff) { this->falloff_ = falloff; }

  // Render functions
  virtual Texture renderImage(Scene const& scene,
                              Camera const& camera,
                              int width, int height);

private:
  float falloff_;
  Color hazeColor_;

};

#endif
