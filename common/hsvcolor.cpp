#include "hsvcolor.h"

HSVColor::HSVColor(float r, float g, float b) {
    float max = std::max(r,g);
    max = std::max(max, b);
    float min = std::min(r,g);
    min = std::min(min, b);
    float delta = max - min;
    this->v = max;

    if (max == min) {
        this->h = 0;
    } else if (max == r) {
        this->h = 60 * (0 + (g-b) / delta);
    } else if (max == g) {
        this->h = 60 * (2 + (b-r) / delta);
    } else {
        this->h = 60 * (4 + (r-g) / delta);
    }

    if (h < 0) {
        h += 360;
    }

    if (max == 0) {
        this->s = 0;
    } else {
        this->s = delta / max;
    }
}

Color HSVColor::getRGBColor() {
    float hi = this->h / 60;
    float f = this->h /60 - hi;
    float p = this->v * (1 - this->s);
    float q = this->v * (1 - this->s - f);
    float t = this->v * (1 - this->s * (1 - f));

    float r,g,b;

    switch ((int) hi) {
    case 0:
        r = this->v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = this->v;
        b = p;
    case 2:
        r = p;
        g = this->v;
        b = t;
    case 3:
        r = p;
        g = q;
        b = this->v;
    case 4:
        r = t;
        g = p;
        b = this->v;
    case 5:
        r = this->v;
        g = p;
        b = q;
    case 6:
        r = this->v;
        g = t;
        b = p;
        break;
    default:
        break;
    }

    return Color(r,g,b);
}
