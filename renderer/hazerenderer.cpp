#include "renderer/hazerenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "common/benchmark.h"
#include "common/progressbar.h"

#include <iostream>
#include <omp.h>

Texture HazeRenderer::renderImage(Scene const& scene,
                                    Camera const& camera,
                                    int width, int height) {
  std::cout << "(HazeRenderer): Rendering..." << std::endl;

  // Setup timer and progressbar
  ProgressBar bar(70);
  bar.start();

  Timer timer;
  timer.start();

  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {

    // Peform for-statement on seperate threads
    #pragma omp parallel for
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay((static_cast<float>(x)/width*2-1),
                               (static_cast<float>(y)/height*2-1)*aspectRatio);
      Color const color = scene.traceRay(&ray);
      float const haze = std::exp(-ray.length*this->falloff_);
      image.setPixelAt(x, y, clamped(color*haze + this->hazeColor_*(1.0-haze)));
    }

    bar.progress((float)(x) / width);
  }

  // Stop timer and progressbar
  timer.end();
  bar.end();
  std::cout << "(HazeRenderer): Rendering time: " << timer.getMilliseconds().count() << " milliseconds." << std::endl;

  return image;
}
