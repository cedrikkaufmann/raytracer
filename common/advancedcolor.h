#ifndef ADVANCEDCOLOR_H
#define ADVANCEDCOLOR_H

#include "common/color.h"

struct AdvancedColor {
  // Components
  float r,g,b,h,s,l;

  // Enum for readability
  enum Channel { R,G,B,H,S,L };

  // Constructor
  AdvancedColor(float r, float g, float b);

  Color getColor();

  void setRGB(float r, float g, float b);
  void setHSL(float h, float s, float l);
  void setChannel(int channel, float value);

  // Access operators
  float & operator[](int channel);
  float const& operator[](int channel) const;
};

#endif
