#ifndef VECTOR3D_SSE_H
#define VECTOR3D_SSE_H

#include <smmintrin.h>
#include <cassert>

class Vector3d
{
 public:
  // Enum for readability
  enum Dimension { X,Y,Z };

  // constructors
  inline Vector3d() : mmvalue(_mm_setzero_ps()) {}
  inline Vector3d(float x, float y, float z) : mmvalue(_mm_set_ps(0, z, y, x)) {}
  inline Vector3d(__m128 m) : mmvalue(m) {}

  // arithmetic operators with Vector3d
  inline Vector3d operator+(const Vector3d& v) const { return _mm_add_ps(mmvalue, v.mmvalue); }
  inline Vector3d operator-(const Vector3d& v) const { return _mm_sub_ps(mmvalue, v.mmvalue); }
  inline Vector3d operator*(const Vector3d& v) const { return _mm_mul_ps(mmvalue, v.mmvalue); }
  inline Vector3d operator/(const Vector3d& v) const { return _mm_div_ps(mmvalue, v.mmvalue); }

  // op= operators
  inline Vector3d& operator+=(const Vector3d& v) { mmvalue = _mm_add_ps(mmvalue, v.mmvalue); return *this; }
  inline Vector3d& operator-=(const Vector3d& v) { mmvalue = _mm_sub_ps(mmvalue, v.mmvalue); return *this; }
  inline Vector3d& operator*=(const Vector3d& v) { mmvalue = _mm_mul_ps(mmvalue, v.mmvalue); return *this; }
  inline Vector3d& operator/=(const Vector3d& v) { mmvalue = _mm_div_ps(mmvalue, v.mmvalue); return *this; }

  // arithmetic operators with float
  inline Vector3d operator+(float v) const { return _mm_add_ps(mmvalue, _mm_set1_ps(v)); }
  inline Vector3d operator-(float v) const { return _mm_sub_ps(mmvalue, _mm_set1_ps(v)); }
  inline Vector3d operator*(float v) const { return _mm_mul_ps(mmvalue, _mm_set1_ps(v)); }
  inline Vector3d operator/(float v) const { return _mm_div_ps(mmvalue, _mm_set1_ps(v)); }

  // op= operators with float
  inline Vector3d& operator+=(float v) { mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(v)); return *this; }
  inline Vector3d& operator-=(float v) { mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(v)); return *this; }
  inline Vector3d& operator*=(float v) { mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(v)); return *this; }
  inline Vector3d& operator/=(float v) { mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(v)); return *this; }

  // Access operators
  float & operator[](int const dimension) {
      assert(0 <= dimension && dimension < 3);
      switch (dimension) {
        case Dimension::X: return this->x;
        case Dimension::Y: return this->y;
        case Dimension::Z: return this->z;
        default: // This must never happen
            return this->x;
      }
   }

   float const& operator[](int const dimension) const {
      assert(0 <= dimension && dimension < 3);
      switch (dimension) {
        case Dimension::X: return this->x;
        case Dimension::Y: return this->y;
        case Dimension::Z: return this->z;
        default: // This must never happen
            return this->x;
      }
   }

  // Member variables
  union {
   struct { float x, y, z; };
   __m128 mmvalue;
  };
};

// Comparison operators ////////////////////////////////////////////////////////

inline bool operator==(Vector3d const& left, Vector3d const& right) { return _mm_test_all_ones(_mm_cmpeq_epi8(left.mmvalue, right.mmvalue)); }
inline bool operator!=(Vector3d const& left, Vector3d const& right) { return !(left == right); }

// Arithmethic operators float with Vector3d
inline Vector3d operator+(float a, const Vector3d& b) { return b + a; }
inline Vector3d operator-(float a, const Vector3d& b) { return Vector3d(_mm_set1_ps(a)) - b; }
inline Vector3d operator*(float a, const Vector3d& b) { return b * a; }
inline Vector3d operator/(float a, const Vector3d& b) { return Vector3d(_mm_set1_ps(a)) / b; }

// Useful functions
inline Vector3d componentProduct(Vector3d const& left, Vector3d const& right) { return _mm_mul_ps(left.mmvalue, right.mmvalue); }
inline Vector3d componentQuotient(Vector3d const& left, Vector3d const& right) { return _mm_div_ps(left.mmvalue, right.mmvalue); }
inline Vector3d crossProduct(Vector3d const& left, Vector3d const& right) {
    return _mm_sub_ps(
     _mm_mul_ps(_mm_shuffle_ps(left.mmvalue, left.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(right.mmvalue, right.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
     _mm_mul_ps(_mm_shuffle_ps(left.mmvalue, left.mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(right.mmvalue, right.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)))
    );
}
inline float dotProduct(Vector3d const& left, Vector3d const& right) { return _mm_cvtss_f32(_mm_dp_ps(left.mmvalue, right.mmvalue, 0x71)); }
inline float length(Vector3d const& v) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v.mmvalue, v.mmvalue, 0x71))); }
inline Vector3d normalized(Vector3d const& v) { return _mm_mul_ps(v.mmvalue, _mm_rsqrt_ps(_mm_dp_ps(v.mmvalue, v.mmvalue, 0x7F))); }
inline void normalize(Vector3d * v) { *v = normalized(*v); }

#endif
