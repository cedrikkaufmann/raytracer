#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "camera/camera.h"

class PerspectiveCamera : public Camera {

public:
  // Constructor / Destructor
  PerspectiveCamera();
  virtual ~PerspectiveCamera() {}

  // Get
  Vector3d position() { return this->position_; }
  Vector3d forwardDirection() { return this->forwardDirection_; }
  Vector3d upDirection() { return this->upDirection_; }
  float fovAngle() { return this->fovAngle_; }

  // Set
  void setPosition(Vector3d const& position) { this->position_ = position; }
  void setForwardDirection(Vector3d const& forwardDirection) { this->forwardDirection_ = normalized(forwardDirection); }
  void setUpDirection(Vector3d const& upDirection) { this->upDirection_ = normalized(upDirection); }
  void setFovAngle(float fovAngle) { this->fovAngle_ = fovAngle; }

  // Camera functions
  virtual Ray castRay(float x, float y) const;

protected:
  Vector3d position_;
  Vector3d forwardDirection_;
  Vector3d upDirection_;
  float fovAngle_;

};

#endif
