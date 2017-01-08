#ifndef TEXTURE_H
#define TEXTURE_H

#include <QColor>
#include <QImage>
#include "common/color.h"
#include "common/vector2d.h"

class Texture {

public:
  // Constructor
  Texture(int width = 0, int height = 0)
    : image_(width, height, QImage::Format_RGB32) {}
  Texture(char const* fileName)
    : image_(fileName) {}

  // Image functions
  void resize(int width, int height) { this->image_ = this->image_.scaled(width, height); }
  bool load(char const* fileName) { return this->image_.load(fileName); }
  bool save(char const* fileName) { return this->image_.save(fileName); }
  bool savePPM(char const* fileName);

  // Get
  bool isNull() const { return this->image_.isNull(); }
  int width() const { return this->image_.width(); }
  int height() const { return this->image_.height(); }
  Color pixel(int x, int y) const {
    QColor const c = image_.pixel(x,y);
    return Color(c.redF(), c.greenF(), c.blueF());
  }

  // Set
  void setPixelAt(int x, int y, Color const& color) {
    Color const c = clamped(color);
    image_.setPixel(x, y, QColor(c.r*255, c.g*255, c.b*255).rgb());
  }

  // Color functions
  Color color(float u, float v) const;
  Color color(Vector2d const& surfacePosition) const;

private:
  QImage image_;

};

#endif
