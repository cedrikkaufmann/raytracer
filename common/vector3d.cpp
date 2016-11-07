#include <cassert>
#include <cmath>
#include "common/vector3d.h"


// Access operators ////////////////////////////////////////////////////////////

float & Vector3d::operator[](int const dimension) {
  assert(0 <= dimension && dimension < 3);
  switch (dimension) {
  case Dimension::X: return this->x;
  case Dimension::Y: return this->y;
  case Dimension::Z: return this->z;
  default: // This must never happen
    return this->x;
  }
}

float const& Vector3d::operator[](int const dimension) const {
  assert(0 <= dimension && dimension < 3);
  switch (dimension) {
  case Dimension::X: return this->x;
  case Dimension::Y: return this->y;
  case Dimension::Z: return this->z;
  default: // This must never happen
    return this->x;
  }
}



// Comparison operators ////////////////////////////////////////////////////////

bool operator==(Vector3d const& left, Vector3d const& right) {
  return (left.x == right.x && left.y == right.y && left.z == right.z);
}

bool operator!=(Vector3d const& left, Vector3d const& right) {
  return !(left == right);
}



// Arithmetic operators ////////////////////////////////////////////////////////

Vector3d operator+(Vector3d const& left, Vector3d const& right) {
  return Vector3d(left.x+right.x, left.y+right.y, left.z+right.z);
}

Vector3d operator-(Vector3d const& right) {
  return Vector3d(-right.x, -right.y, -right.z);
}

Vector3d operator-(Vector3d const& left, Vector3d const& right) {
  return Vector3d(left.x-right.x, left.y-right.y, left.z-right.z);
}

Vector3d operator*(Vector3d const& left, float right) {
  return Vector3d(left.x*right, left.y*right, left.z*right);
}

Vector3d operator*(float left, Vector3d const& right) {
  return Vector3d(left*right.x, left*right.y, left*right.z);
}

Vector3d operator/(Vector3d const& left, float right) {
  return Vector3d(left.x/right, left.y/right, left.z/right);
}



// Assignment operators ////////////////////////////////////////////////////////

Vector3d & operator+=(Vector3d & left, Vector3d const& right) {
  left.x += right.x;
  left.y += right.y;
  left.z += right.z;
  return left;
}

Vector3d & operator-=(Vector3d & left, Vector3d const& right) {
  left.x -= right.x;
  left.y -= right.y;
  left.z -= right.z;
  return left;
}

Vector3d & operator*=(Vector3d & left, float right) {
  left.x *= right;
  left.y *= right;
  left.z *= right;
  return left;
}

Vector3d & operator/=(Vector3d & left, float right) {
  left.x /= right;
  left.y /= right;
  left.z /= right;
  return left;
}



// Useful functions ////////////////////////////////////////////////////////////

Vector3d componentProduct(const Vector3d &left, const Vector3d &right) {
  return Vector3d(left.x*right.x, left.y*right.y, left.z*right.z);
}

Vector3d componentQuotient(const Vector3d &left, const Vector3d &right) {
  return Vector3d(left.x/right.x, left.y/right.y, left.z/right.z);
}

Vector3d crossProduct(Vector3d const& left, Vector3d const& right) {
  return Vector3d(left.y*right.z - left.z*right.y,
                  left.z*right.x - left.x*right.z,
                  left.x*right.y - left.y*right.x);
}

float dotProduct(Vector3d const& left, Vector3d const& right) {
  return left.x*right.x + left.y*right.y + left.z*right.z;
}

float length(Vector3d const& v) {
  return std::sqrt(dotProduct(v,v));
}

Vector3d normalized(Vector3d const& v) {
  return v/length(v);
}

void normalize(Vector3d * v) {
  *v = normalized(*v);
}


