#include "renderer/backgroundrenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "common/benchmark.h"
#include "common/progressbar.h"

#include <iostream>
#include <omp.h>

Texture BackgroundRenderer::renderImage(Scene const& scene,
                                        Camera const& camera,
                                        int width, int height) {
  std::cout << "(BackgroundRenderer): Rendering..." << std::endl;

  // Setup timer and progressbar
  ProgressBar bar(70);
  bar.start();

  Timer timer;
  timer.start();

  Texture image(width, height);
  for (int x = 0; x < image.width(); ++x) {

    // Peform for-statement on seperate threads
    #pragma omp parallel for
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay(static_cast<float>(x)/width,
                               static_cast<float>(y)/height);
      image.setPixelAt(x, y, clamped(scene.traceRay(&ray)));
    }

    bar.progress((float)(x) / width);
  }

  // Stop timer and progressbar
  timer.end();
  bar.end();
  std::cout << "(BackgroundRenderer): Rendering time: " << timer.getMilliseconds().count() << " milliseconds." << std::endl;

  return image;
}
