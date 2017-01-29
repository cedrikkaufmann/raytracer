#include "renderer/depthoffieldrenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "common/progressbar.h"
#include "common/benchmark.h"
#include "common/vector2d.h"

#include <time.h>
#include <omp.h>
#include <iostream>


Vector3d unitCircleRandom(float radius) {
  Vector2d randomVec(
    2*PI*((float)rand() / RAND_MAX),
    std::sqrt((float)rand() / RAND_MAX)
  );

  Vector2d circleVec = Vector2d(std::cos(randomVec.u), std::sin(randomVec.v));
  Vector2d unitCirclePos = ( (radius * randomVec.v) * circleVec );

  return Vector3d(unitCirclePos.u, unitCirclePos.v, 0);
}

Texture DepthOfFieldRenderer::renderImage(Scene const& scene,
                                    Camera const& camera,
                                    int width, int height) {
  std::cout << "(DepthOfFieldRenderer): Rendering..." << std::endl;

  // Setup timer and progressbar
  ProgressBar bar(70);
  bar.start();

  Timer timer;
  timer.start();

  // Initialize random generator
  srand( (unsigned) time(NULL) * omp_get_thread_num());

  Texture image(width, height);

  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {

    // Peform for-statement on seperate threads
    #pragma omp parallel for
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay((static_cast<float>(x)/width*2-1),
                               (static_cast<float>(y)/height*2-1)*aspectRatio);

      // Calculate the focal point on the focal plane
      Vector3d focalPoint = ray.origin + this->focalDistance_ * ray.direction;

      // Aperture color buffer
      Color apertureColor;

      for (unsigned i = 0; i < this->apertureRays_; i++) {
        // prepare ray using jittered random origin simulating the aperture
        Ray apertureRay = ray;
        apertureRay.origin += unitCircleRandom(this->apertureRadius_);

        // calculate new direction based on focal point and jittered origin
        apertureRay.direction = normalized(focalPoint - apertureRay.origin);

        // trace the aperture ray and add color to color buffer
        apertureColor += scene.traceRay(&apertureRay);
      }

      // calculate average over color buffer and set the color
      apertureColor = apertureColor / this->apertureRays_;
      image.setPixelAt(x, y, clamped(apertureColor));
    }

    bar.progress((float)(x) / width);
  }

  // Stop timer and progressbar
  timer.end();
  bar.end();
  std::cout << "(DepthOfFieldRenderer): Rendering time: " << timer.getMilliseconds().count() << " milliseconds." << std::endl;

  return image;
}
