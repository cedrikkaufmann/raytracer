#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include "common/color.h"
#include "common/vector2d.h"

class Texture {

public:
  // Constructor
  Texture(int width = 0, int height = 0);
  Texture(char const* fileName);

  // Image functions
  void resize(int width, int height);
  bool load(char const* fileName);
  bool save(char const* fileName) const;

  // Get
  bool isNull() const { return this->image_.empty(); }
  int width() const { return this->image_.size(); }
  int height() const { return (!this->image_.empty() ? this->image_[0].size() : 0); }
  Color pixel(int x, int y) const;

  // Set
  void setPixelAt(int x, int y, Color const& color);

  // Color functions
  Color color(float u, float v) const;
  Color color(Vector2d const& surfacePosition) const;

private:
  std::vector< std::vector<Color> > image_;

};

#endif
