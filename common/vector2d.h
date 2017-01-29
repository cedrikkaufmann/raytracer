#ifndef VECTOR2D_SSE_H
#define VECTOR2D_SSE_H

#include <smmintrin.h>
#include <cassert>

class Vector2d
{
 public:
  // Enum for readability
  enum Dimension { U,V };

  // constructors
  inline Vector2d() : mmvalue(_mm_setzero_ps()) {}
  inline Vector2d(float u, float v) : mmvalue(_mm_set_ps(0, 0, v, u)) {}
  inline Vector2d(__m128 m) : mmvalue(m) {}

  // arithmetic operators with Vector2d
  inline Vector2d operator+(const Vector2d& m) const { return _mm_add_ps(mmvalue, m.mmvalue); }
  inline Vector2d operator-(const Vector2d& m) const { return _mm_sub_ps(mmvalue, m.mmvalue); }
  inline Vector2d operator*(const Vector2d& m) const { return _mm_mul_ps(mmvalue, m.mmvalue); }
  inline Vector2d operator/(const Vector2d& m) const { return _mm_div_ps(mmvalue, m.mmvalue); }

  // assigment operators with Vector2d
  inline Vector2d& operator+=(const Vector2d& m) { mmvalue = _mm_add_ps(mmvalue, m.mmvalue); return *this; }
  inline Vector2d& operator-=(const Vector2d& m) { mmvalue = _mm_sub_ps(mmvalue, m.mmvalue); return *this; }
  inline Vector2d& operator*=(const Vector2d& m) { mmvalue = _mm_mul_ps(mmvalue, m.mmvalue); return *this; }
  inline Vector2d& operator/=(const Vector2d& m) { mmvalue = _mm_div_ps(mmvalue, m.mmvalue); return *this; }

  // arithmetic operators with float
  inline Vector2d operator+(float m) const { return _mm_add_ps(mmvalue, _mm_set1_ps(m)); }
  inline Vector2d operator-(float m) const { return _mm_sub_ps(mmvalue, _mm_set1_ps(m)); }
  inline Vector2d operator*(float m) const { return _mm_mul_ps(mmvalue, _mm_set1_ps(m)); }
  inline Vector2d operator/(float m) const { return _mm_div_ps(mmvalue, _mm_set1_ps(m)); }

  // assignment operators with float
  inline Vector2d& operator+=(float m) { mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(m)); return *this; }
  inline Vector2d& operator-=(float m) { mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(m)); return *this; }
  inline Vector2d& operator*=(float m) { mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(m)); return *this; }
  inline Vector2d& operator/=(float m) { mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(m)); return *this; }

  // Access operators
  float & operator[](int dimension) {
    assert(0 <= dimension && dimension < 2);
    switch (dimension) {
    case Dimension::U: return this->u;
    case Dimension::V: return this->v;
    default: // This must never happen
      return this->u;
    }
  }

  float const& operator[](int dimension) const {
    assert(0 <= dimension && dimension < 2);
    switch (dimension) {
    case Dimension::U: return this->u;
    case Dimension::V: return this->v;
    default: // This must never happen
      return this->u;
    }
  }

  // Member variables
  union {
   struct { float u, v; };
   __m128 mmvalue;
  };
};

// Comparison operators ////////////////////////////////////////////////////////
inline bool operator==(Vector2d const& left, Vector2d const& right) { return _mm_test_all_ones(_mm_cmpeq_epi32(left.mmvalue, right.mmvalue)); }
inline bool operator!=(Vector2d const& left, Vector2d const& right) { return !(left == right); }

// Arithmethic operators float with Vector3d
inline Vector2d operator+(float a, const Vector2d& b) { return b + a; }
inline Vector2d operator-(float a, const Vector2d& b) { return Vector2d(_mm_set1_ps(a)) - b; }
inline Vector2d operator*(float a, const Vector2d& b) { return b * a; }
inline Vector2d operator/(float a, const Vector2d& b) { return Vector2d(_mm_set1_ps(a)) / b; }

// Useful functions
inline Vector2d componentProduct(Vector2d const& left, Vector2d const& right) { return _mm_mul_ps(left.mmvalue, right.mmvalue); }
inline Vector2d componentQuotient(Vector2d const& left, Vector2d const& right) { return _mm_div_ps(left.mmvalue, right.mmvalue); }
inline float dotProduct(Vector2d const& left, Vector2d const& right) { return _mm_cvtss_f32(_mm_dp_ps(left.mmvalue, right.mmvalue, 0x71)); }
inline float length(Vector2d const& m) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(m.mmvalue, m.mmvalue, 0x71))); }
inline Vector2d normalized(Vector2d const& m) { return _mm_mul_ps(m.mmvalue, _mm_rsqrt_ps(_mm_dp_ps(m.mmvalue, m.mmvalue, 0x7F))); }
inline void normalize(Vector2d * m) { *m = normalized(*m); }

#endif
