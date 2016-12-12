#include "renderer/depthrenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "common/progressbar.h"

Texture DepthRenderer::renderImage(Scene const& scene,
                                   Camera const& camera,
                                   int width, int height) {
  ProgressBar bar(70);
  bar.start();

  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  float minDepth = +INFINITY;
  float maxDepth = -INFINITY;
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay((static_cast<float>(x)/width*2-1),
                               (static_cast<float>(y)/height*2-1)*aspectRatio);
      if (scene.findOcclusion(&ray)) {
        float const depth = ray.length;
        minDepth = std::min(minDepth,depth);
        maxDepth = std::max(maxDepth,depth);
        image.setPixelAt(x, y, Color(1,1,1)*depth);
      } else {
        image.setPixelAt(x, y, Color(1,1,1)*INFINITY);
      }
    }

    bar.progress((float)x/(image.width() * 2));
  }

  // Normalize the depth values
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
      Color const depth = (image.pixel(x,y) - Color(1,1,1)*minDepth) / (maxDepth-minDepth);
      image.setPixelAt(x,y, Color(1,1,1) - depth);
    }

    bar.progress(((float)x + image.width())/(image.width() * 2));
  }

  bar.end();

  std::cout << "Rendering time: " << bar.progressTime << " sec." << std::endl;

  return image;
}
