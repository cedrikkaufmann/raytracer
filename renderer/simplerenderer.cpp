#include <cstdio>
#include "renderer/simplerenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"

Texture SimpleRenderer::renderImage(Scene const& scene,
                                    Camera const& camera,
                                    int width, int height) {
  // Super-hacky progress bar!
  int k = 0;
  printf("(SimpleRenderer): Begin rendering...\n");
  printf("| 0%%");
  int const barSize = 50;
  int const stepSize = (width*height)/barSize;
  for (int i = 0; i < barSize-3-5; ++i)
    printf(" ");
  printf("100%% |\n|");

  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay((static_cast<float>(x)/width*2-1),
                               (static_cast<float>(y)/height*2-1)*aspectRatio);
      image.setPixelAt(x, y, clamped(scene.traceRay(&ray)));

      // Super hacky progress bar!
      if (++k % stepSize == 0)
        printf("=");
    }
  }
  printf("|\n");
  return image;
}
