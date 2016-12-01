#include "renderer/desaturationrenderer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "common/progressbar.h"
#include "common/hsvcolor.h"

#include <time.h>

Texture DesaturationRenderer::renderImage(Scene const& scene,
                                    Camera const& camera,
                                    int width, int height) {

  double time1= 0.0, tstart;
  tstart = clock();

  ProgressBar bar(70);
  Texture image(width, height);
  float const aspectRatio = static_cast<float>(height)/width;
  for (int x = 0; x < image.width(); ++x) {
    for (int y = 0; y < image.height(); ++y) {
      Ray ray = camera.castRay((static_cast<float>(x)/width*2-1),
                               (static_cast<float>(y)/height*2-1)*aspectRatio);

      Color c = clamped(scene.traceRay(&ray));

      HSVColor hsv(c.r, c.g, c.b);
      hsv.s = hsv.s * intensity();
      image.setPixelAt(x, y, hsv.getRGBColor());

      //float average = (c.r + c.g + c.b) / 3;
      //Color gray(average, average, average);
      //image.setPixelAt(x, y, c * gray * intensity());
    }

    bar.progress((float)x/image.width());
  }

  bar.end();

  time1 += clock() - tstart;
  time1 = time1 / CLOCKS_PER_SEC;

  std::cout << "Rendering time: " << time1 << " sec." << std::endl;

  return image;
}
