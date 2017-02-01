#include "renderer/superrenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "common/progressbar.h"
#include "common/benchmark.h"

#include <iostream>
#include <omp.h>

Texture SuperRenderer::renderImage(Scene const& scene,
                                Camera const& camera,
                                int width, int height) {
  std::cout << "(SuperRenderer): Rendering..." << std::endl;

  // Setup timer and progressbar
  ProgressBar bar(70);
  bar.start();

  Timer timer;
  timer.start();

  // A few helpful constants
  int const sampleCount = this->superSamplingFactor_*this->superSamplingFactor_;
  float const samplingStep = 1.0f/this->superSamplingFactor_;

  // The usual render loop
  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {

    // Peform for-statement on seperate threads
    #pragma omp parallel for
    for (int y = 0; y < image.height(); ++y) {
      // The fragment color is averaged over all sub-pixel rays
      Color fragmentColor;
      for (int xs = 0; xs < this->superSamplingFactor_; ++xs) {

        for (int ys = 0; ys < this->superSamplingFactor_; ++ys) {
          Ray ray = camera.castRay(((xs* (samplingStep + rand()/RAND_MAX / this->superSamplingFactor_ ) + x)/width*2-1),
                                   ((ys* (samplingStep + rand()/RAND_MAX / this->superSamplingFactor_ ) + y)/height*2-1)*aspectRatio);
          fragmentColor += scene.traceRay(&ray);
        }
      }
      image.setPixelAt(x, y, clamped(fragmentColor/sampleCount));
    }

    bar.progress((float)(x) / width);
  }

  // Stop timer and progressbar
  timer.end();
  bar.end();
  std::cout << "(SuperRenderer): Rendering time: " << timer.getMilliseconds().count() << " milliseconds." << std::endl;

  return image;
}
