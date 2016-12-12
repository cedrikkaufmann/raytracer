#include "renderer/hazerenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "common/progressbar.h"

Texture HazeRenderer::renderImage(Scene const& scene,
                                    Camera const& camera,
                                    int width, int height) {
  ProgressBar bar(70);
  bar.start();

  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay((static_cast<float>(x)/width*2-1),
                               (static_cast<float>(y)/height*2-1)*aspectRatio);
      Color const color = scene.traceRay(&ray);
      float const haze = std::exp(-ray.length*this->falloff_);
      image.setPixelAt(x, y, clamped(color*haze + this->hazeColor_*(1.0-haze)));
    }

    bar.progress((float)x/image.width());
  }

  bar.end();

  std::cout << "Rendering time: " << bar.progressTime << " sec." << std::endl;

  return image;
}
