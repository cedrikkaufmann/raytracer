#include "renderer/simplerenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"

Texture SimpleRenderer::renderImage(Scene const& scene,
                                    Camera const& camera,
                                    int width, int height) {
  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay((static_cast<float>(x)/width*2-1),
                               (static_cast<float>(y)/height*2-1)*aspectRatio);  
      image.setPixelAt(x, y, clamped(scene.traceRay(&ray)));
    }
  }
  return image;
}
