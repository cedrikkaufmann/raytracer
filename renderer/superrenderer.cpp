#include <cstdio>
#include "renderer/superrenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "common/progressbar.h"

Texture SuperRenderer::renderImage(Scene const& scene,
                                    Camera const& camera,
                                    int width, int height) {
  ProgressBar bar(70);
  bar.start();

  Texture image(width, height);

  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
        float renderPosX = (static_cast<float>(x)/width*2-1);
        float renderPosY =  (static_cast<float>(y)/height*2-1)*aspectRatio;

        Color superSampledColor;

        for (int a = 0; a < superSamplingFactor(); a++) {
            for (int b = 0; b < superSamplingFactor(); b++) {
                Ray ray = camera.castRay(renderPosX + a, renderPosY + b);
                superSampledColor += clamped(scene.traceRay(&ray));
            }
        }

        superSampledColor = superSampledColor / (superSamplingFactor() * superSamplingFactor());

        image.setPixelAt(x, y, superSampledColor);
    }

    bar.progress((float)(x) / image.width());
  }

  bar.end();
  std::cout << "Rendering time: " << bar.progressTime << " sec." << std::endl;

  return image;
}
