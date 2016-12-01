#ifndef HSVCOLOR_H
#define HSVCOLOR_H

#include <string>
#include "common/color.h"

struct HSVColor {
  // Components
  float h,s,v;

  // Enum for readability
  enum Channel { H,S,V };

  // Constructor
  HSVColor(float r, float g, float b);

  Color getRGBColor();
};

#endif
