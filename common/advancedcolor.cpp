#include "advancedcolor.h"
#include <cassert>
#include <algorithm>
#include <string>
#include <cmath>

AdvancedColor::AdvancedColor(float r, float g, float b) {
    setRGB(r,g,b);
}

void AdvancedColor::setRGB(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;

    // caluclate max, min and delta
    float cmax = std::max(r,g);
    cmax = std::max(cmax,b);
    float cmin = std::min(r,g);
    cmin = std::min(cmin,b);
    float delta = cmax - cmin;

    // lightness calculation
    this->l = (cmax + cmin) * 0.5f;

    // hue calculation
    if (delta == 0 || delta <= std::numeric_limits<float>::epsilon()) {
        this->h = 0;
    } else if (cmax == r) {
        this->h = ( (int)((g-b) / delta) % 6 );
    } else if (cmax == g) {
        this->h = ((b-r) / delta) + 2;
    } else if (cmax == b) {
        this->h = ((r-g) / delta) + 4;
    }
    this->h *= 60;

    // saturation calculation
    if (delta == 0 || delta <= std::numeric_limits<float>::epsilon()) {
        this->s = 0;
    } else {
        this->s = delta / (1 - std::abs(2 * this->l - 1) );
    }
}

void AdvancedColor::setHSL(float h, float s, float l) {
    this->h = h;
    this->s = s;
    this->l = l;

    float c = ( 1 -  std::abs( 2 * l - 1 ) ) * s;
    float temp = (int)(H / 60) % 2 - 1;
    float x = c * ( 1 - std::abs(temp));
    float m = l - c/0.5f;

    if (h >= 0 && h < 60) {
        this->r = c;
        this->g = x;
        this->b = 0;
    } else if (h >= 60 && h < 120) {
        this->r = x;
        this->g = c;
        this->b = 0;
    } else if (h >= 120 && h < 180) {
        this->r = 0;
        this->g = c;
        this->b = x;
    } else if (h >= 180 && h < 240) {
        this->r = 0;
        this->g = x;
        this->b = c;
    } else if (h >= 240 && h < 300) {
        this->r = x;
        this->g = 0;
        this->b = c;
    } else if (h >= 300 && h < 360) {
        this->r = c;
        this->g = 0;
        this->b = x;
    }
}

void AdvancedColor::setChannel(int channel, float value) {
    assert(0 <= channel && channel < 6);
    switch (channel) {
    case Channel::R:
        setRGB(value, this->g, this->b);
        break;
    case Channel::G:
        setRGB(this->g, value, this->b);
        break;
    case Channel::B:
        setRGB(this->r, this->g, value);
        break;
    case Channel::H:
        setHSL(value, this->s, this->l);
        break;
    case Channel::S:
        setHSL(this->h, value, this->l);
        break;
    case Channel::L:
        setHSL(this->h, this->s, value);
        break;
    }
}

Color AdvancedColor::getColor() {
    return Color(this->r, this->g, this->b);
}

// Access operators ////////////////////////////////////////////////////////////

float & AdvancedColor::operator[](int channel) {
  assert(0 <= channel && channel < 6);
  switch (channel) {
  case Channel::R: return this->r;
  case Channel::G: return this->g;
  case Channel::B: return this->b;
  case Channel::H: return this->h;
  case Channel::S: return this->s;
  case Channel::L: return this->l;
  default: // This must never happen
    return this->r;
  }
}

float const& AdvancedColor::operator[](int channel) const {
  assert(0 <= channel && channel < 6);
  switch (channel) {
  case Channel::R: return this->r;
  case Channel::G: return this->g;
  case Channel::B: return this->b;
  case Channel::H: return this->h;
  case Channel::S: return this->s;
  case Channel::L: return this->l;
  default: // This must never happen
    return this->r;
  }
}
