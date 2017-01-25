#include <cstdio>
#include "renderer/superrenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"

Texture SuperRenderer::renderImage(Scene const& scene,
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

  // A few helpful constants
  int const sampleCount = this->superSamplingFactor_*this->superSamplingFactor_;
  float const samplingStep = 1.0f/this->superSamplingFactor_;

  // The usual render loop
  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {

      // The fragment color is averaged over all sub-pixel rays
      Color fragmentColor;
      for (int xs = 0; xs < this->superSamplingFactor_; ++xs) {
        for (int ys = 0; ys < this->superSamplingFactor_; ++ys) {
          Ray ray = camera.castRay(((xs*samplingStep + x)/width*2-1),
                                   ((ys*samplingStep + y)/height*2-1)*aspectRatio);
          fragmentColor += scene.traceRay(&ray);
        }
      }
      image.setPixelAt(x, y, clamped(fragmentColor/sampleCount));

      // Super hacky progress bar!
      if (++k % stepSize == 0)
        printf("=");

    }
  }
  printf("|\n");
  return image;
}
