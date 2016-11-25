#include "renderer/simplerenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"

#include <iostream>
#include <time.h>

Texture SimpleRenderer::renderImage(Scene const& scene,
                                    Camera const& camera,
                                    int width, int height) {

  double time1= 0.0, tstart;
  tstart = clock();

  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay((static_cast<float>(x)/width*2-1),
                               (static_cast<float>(y)/height*2-1)*aspectRatio);
      image.setPixelAt(x, y, clamped(scene.traceRay(&ray)));
    }

    float progress = (float)x/image.width();

    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
  }

  std::cout << std::endl;

  time1 += clock() - tstart;
  time1 = time1 / CLOCKS_PER_SEC;

  std::cout << "Rendering time: " << time1 << " sec." << std::endl;

  return image;
}
