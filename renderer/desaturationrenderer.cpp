#include "renderer/desaturationrenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"

Texture DesaturationRenderer::renderImage(Scene const& scene,
                                          Camera const& camera,
                                          int width, int height) {
  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay((static_cast<float>(x)/width*2-1),
                               (static_cast<float>(y)/height*2-1)*aspectRatio);
      Color const color = scene.traceRay(&ray);
      float const gray = (color.r + color.g + color.b)/3;
      image.setPixelAt(x, y, clamped((1-this->intensity_)*color + this->intensity_*Color(gray,gray,gray)));
    }
  }
  return image;
}
