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
  //for (int y = resY-1; y >= 0; --y) {
    for (int x = 0; x < resX; ++x)
    //for (int x = resX-1; x >= 0; --x)
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
  if ((x %= this->width()) < 0)
      x += this->width();
    if ((y %= this->height()) < 0)
      y += this->height();
    return this->image_[x][y];
}

void Texture::setPixelAt(int x, int y, Color const& color) {
  if ((x %= this->width()) < 0)
      x += this->width();
    if ((y %= this->height()) < 0)
      y += this->height();
    this->image_[x][y] = color;
}

Color Texture::color(float u, float v) const {
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
  return Color();
}

Color Texture::color(Vector2d const& surfacePosition) const {
  return color(surfacePosition.u, surfacePosition.v);
}
