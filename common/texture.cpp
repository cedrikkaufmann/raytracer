#include <cmath>
#include <fstream>
#include <iostream>
#include "common/texture.h"

Texture::Texture(int width, int height) {
  this->resize(width, height);
}

Texture::Texture(char const* fileName) {
  this->load(fileName);
}

void Texture::resize(int width, int height) {
  std::vector<Color> const column(height);
  this->image_.resize(width);
  for (unsigned int i = 0; i < this->image_.size(); ++i)
    this->image_[i] = column;
}

bool Texture::load(char const* fileName) {
  std::cerr << "(Image): Reading file " << fileName << std::endl;
  std::ifstream file(fileName);

  if (!file.is_open())    {
    std::cerr << "(Image): Could not open file " << fileName << std::endl;
    return false;
  }

  char c;
  c = file.peek();
  while (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r') {
    file.get(c);
    c = file.peek();
  }

  // Peek for comments.
  std::string comment;
  c = file.peek();
  while (c == '#') {
    std::getline(file, comment);
    c = file.peek();
  }

  c = file.peek();
  while (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r') {
    file.get(c);
    c = file.peek();
  }


  std::string magic;
  file >> magic;

  c = file.peek();
  while (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r') {
    file.get(c);
    c = file.peek();
  }

  // Peek for comments.
  c = file.peek();
  while (c == '#') {
    std::getline(file, comment);
    c = file.peek();
  }

  c = file.peek();
  while (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r') {
    file.get(c);
    c = file.peek();
  }

  int depth;
  int resX, resY;
  file >> resX >> resY >> depth;

  this->resize(resX, resY);

  int r, g, b;

  for (int y = 0; y < resY; ++y) {
    for (int x = 0; x < resX; ++x)
    {
      file >> r >> g >> b;
      Color color(static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f);
      this->image_[x][y] = color;
    }
  }

  file.close();
  return true;
}

bool Texture::save(char const* fileName) const {
  if (!this->image_.empty()) {
    std::ofstream file(fileName);
    file << "P3" << std::endl; // Magic number for .ppm
    file << this->image_.size() << " " << this->image_[0].size() << " " << 255 << std::endl;
    for (unsigned int y = 0; y < this->image_[0].size(); ++y) {
      for (unsigned int x = 0; x < this->image_.size(); ++x) {
        file << static_cast<int>(255.99999999 * this->image_[x][y].r) << " "
             << static_cast<int>(255.99999999 * this->image_[x][y].g) << " "
             << static_cast<int>(255.99999999 * this->image_[x][y].b) << " "
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

Color Texture::pixel(int x, int y) const {
  return this->image_[x][y];
}

void Texture::setPixelAt(int x, int y, Color const& color) {
  this->image_[x][y] = color;
}

Color Texture::color(float u, float v) const {
  // calculate nearest rastering coordinates of their texture coordinates
  float x = u* this->width();
  float y = v* this->height();
  float x1 = floor(u* this->width());
  float y1 = floor(v* this->height());

  // check for bounds
  if (x1 < 0)
      x1 = 0;
  if (y1 < 0)
      y1 = 0;

  float x2 = x1+1;
  float y2 = y1+1;

  // check for bounds
  if (x2 > (this->width() - 1)) {
    x2 = this->width() - 1;
    x1 = x2-1;
  }
  if (y2 > (this->height() - 1)) {
    y2 = this->height() - 1;
    y1 = y2-1;
  }

  // pre calculation of coordinate's delta
  float const delta_x_x1 = x-x1;
  float const delta_x2_x = x2-x;
  int const delta_x2_x1 = x2-x1;
  int const delta_y2_y1 = y2-y1;

  // pre calculation of weight coefficient
  float alpha = delta_x2_x / delta_x2_x1;
  float beta = delta_x_x1 / delta_x2_x1;

  // calculate weighted color for pixels of rastering coordinates
  Color f1 = alpha * pixel(x1,y1) + beta * pixel(x2,y1);
  Color f2 = alpha * pixel(x1,y2) + beta * pixel(x2,y2);

  // finally calculate interpolated color
  Color filter( ((y2 - y) / delta_y2_y1) * f1 + ((y - y1) / delta_y2_y1) * f2 );

  return filter;
}

Color Texture::color(Vector2d const& surfacePosition) const {
  return color(surfacePosition.u, surfacePosition.v);
}
