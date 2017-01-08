#include <fstream>
#include "common/texture.h"

Color Texture::color(float u, float v) const {
  if (this->isNull())
    return Color();

  u = u * this->width() - 0.5f;
  v = v * this->height() - 0.5f;
  int const x = std::floor(u);
  int const y = std::floor(v);
  float const u_ratio = u - x;
  float const v_ratio = v - y;
  float const u_opposite = 1.0f - u_ratio;
  float const v_opposite = 1.0f - v_ratio;
  return
      (this->pixel(x,y+0)*u_opposite + this->pixel(x+1,y+0)*u_ratio) * v_opposite +
      (this->pixel(x,y+1)*u_opposite + this->pixel(x+1,y+1)*u_ratio) * v_ratio;
}

Color Texture::color(Vector2d const& surfacePosition) const {
  return color(surfacePosition.u, surfacePosition.v);
}

bool Texture::savePPM(char const* fileName) {
  if (!this->image_.isNull()) {
    std::ofstream file(fileName);
    file << "P3" << std::endl; // Magic number for .ppm
    file << this->image_.width() << " " << this->image_.height() << " " << 255 << std::endl;
    for (int y = this->image_.height()-1; y >= 0; --y) {
      for (int x = 0; x < this->image_.width(); ++x) {
        file << this->image_.pixelColor(x,y).red() << " "
             << this->image_.pixelColor(x,y).green() << " "
             << this->image_.pixelColor(x,y).blue() << " "
             << "\t";
      }
      file << std::endl;
      file << std::flush;
    }
    printf("Image file written to: \"%s\"\n", fileName);
    file.close();
    return true;
  }
  return false;
}
