#ifndef COLOR_SSE_H
#define COLOR_SSE_H

#include <smmintrin.h>
#include <cassert>

class Color
{
 public:
  // Enum for readability
  enum Channel { R,G,B };

  // constructors
  inline Color() : mmvalue(_mm_setzero_ps()) {}
  inline Color(float r, float g, float b) : mmvalue(_mm_set_ps(0, b, g, r)) {}
  inline Color(__m128 m) : mmvalue(m) {}

  // arithmetic operators with Color
  inline Color operator+(const Color& c) const { return _mm_add_ps(mmvalue, c.mmvalue); }
  inline Color operator-(const Color& c) const { return _mm_sub_ps(mmvalue, c.mmvalue); }
  inline Color operator*(const Color& c) const { return _mm_mul_ps(mmvalue, c.mmvalue); }
  inline Color operator/(const Color& c) const { return _mm_div_ps(mmvalue, c.mmvalue); }

  // assignment operators with Color
  inline Color& operator+=(const Color& c) { mmvalue = _mm_add_ps(mmvalue, c.mmvalue); return *this; }
  inline Color& operator-=(const Color& c) { mmvalue = _mm_sub_ps(mmvalue, c.mmvalue); return *this; }
  inline Color& operator*=(const Color& c) { mmvalue = _mm_mul_ps(mmvalue, c.mmvalue); return *this; }
  inline Color& operator/=(const Color& c) { mmvalue = _mm_div_ps(mmvalue, c.mmvalue); return *this; }

  // arithmetic operators with float
  inline Color operator+(float c) const { return _mm_add_ps(mmvalue, _mm_set1_ps(c)); }
  inline Color operator-(float c) const { return _mm_sub_ps(mmvalue, _mm_set1_ps(c)); }
  inline Color operator*(float c) const { return _mm_mul_ps(mmvalue, _mm_set1_ps(c)); }
  inline Color operator/(float c) const { return _mm_div_ps(mmvalue, _mm_set1_ps(c)); }

  // assignment operators with float
  inline Color& operator+=(float v) { mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(v)); return *this; }
  inline Color& operator-=(float v) { mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(v)); return *this; }
  inline Color& operator*=(float v) { mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(v)); return *this; }
  inline Color& operator/=(float v) { mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(v)); return *this; }

  // Access operators
  inline float & operator[](int const channel) {
      assert(0 <= channel && channel < 3);
      switch (channel) {
        case Channel::R: return this->r;
        case Channel::G: return this->g;
        case Channel::B: return this->b;
        default: // This must never happen
            return this->r;
      }
   }

   inline float const& operator[](int const channel) const {
      assert(0 <= channel && channel < 3);
      switch (channel) {
        case Channel::R: return this->r;
        case Channel::G: return this->g;
        case Channel::B: return this->b;
        default: // This must never happen
            return this->r;
      }
   }

  // Member variables
  union {
   struct {
       float r, g, b;
   };
   __m128 mmvalue;
  };
};

// Comparison operators ////////////////////////////////////////////////////////
inline bool operator==(Color const& left, Color const& right) { return _mm_test_all_ones(_mm_cmpeq_epi8(left.mmvalue, right.mmvalue)); }
inline bool operator!=(Color const& left, Color const& right) { return !(left == right); }

// Arithmethic operators float with Color
inline Color operator+(float a, const Color& b) { return b + a; }
inline Color operator-(float a, const Color& b) { return Color(_mm_set1_ps(a)) - b; }
inline Color operator*(float a, const Color& b) { return b * a; }
inline Color operator/(float a, const Color& b) { return Color(_mm_set1_ps(a)) / b; }

inline Color clamped(Color const& c) {
  return _mm_max_ps(_mm_set_ps(0, 0.0f, 0.0f, 0.0f), _mm_min_ps(c.mmvalue, _mm_set_ps(0, 1.0f, 1.0f, 1.0f)));
}

inline void clamp(Color * c) {
  *c = clamped(*c);
}

// Useful functions
inline Color minimum(Color const& left, Color const& right) { return _mm_min_ps(left.mmvalue, right.mmvalue); }
inline Color maximum(Color const& left, Color const& right) { return _mm_max_ps(left.mmvalue, right.mmvalue); }


#endif
