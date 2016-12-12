#ifndef OMNIDIRECTIONALCAMERA_H
#define OMNIDIRECTIONALCAMERA_H

#include "camera/camera.h"

class OmnidirectionalCamera : public Camera {

public:
  // Constructor / Destructor
  OmnidirectionalCamera() {}
  virtual ~OmnidirectionalCamera() {}

  // Get
  Vector3d position() { return this->position_; }

  // Set
  void setPosition(Vector3d const& position) { this->position_ = position; }

  // Camera functions
  virtual Ray castRay(float x, float y) const;

protected:
  Vector3d position_;

};

#endif
