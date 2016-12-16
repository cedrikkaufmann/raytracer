#include "renderer/backgroundrenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "common/progressbar.h"

Texture BackgroundRenderer::renderImage(Scene const& scene,
                                        Camera const& camera,
                                        int width, int height) {
  ProgressBar bar(70);
  bar.start();

  Texture image(width, height);
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay(static_cast<float>(x)/width,
                               static_cast<float>(y)/height);
      image.setPixelAt(x, y, clamped(scene.traceRay(&ray)));
    }

    bar.progress((float)x/image.width());
  }

  bar.end();

  std::cout << "Rendering time: " << bar.progressTime << " sec." << std::endl;

  return image;
}
