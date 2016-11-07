#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "common/color.h"
#include "common/ray.h"
#include "common/texture.h"
#include "common/vector3d.h"

// Forward declarations
class Light;
class Primitive;
class Shader;

class Scene {

public:
  // Constructor / Destructor
  Scene() {}
  virtual ~Scene();

  // Get
  std::vector<Light*> const& lights() { return this->lights_; }
  std::vector<Primitive*> const& primitives() { return this->primitives_; }
  std::vector<Shader*> const& shaders() { return this->shaders_; }

  // Set
  void setBackgroundColor(Color const& color) { this->backgroundColor_ = color; }
  void setEnvironmentMap(Texture const& map) { this->environmentMap_ = map; }

  // Setup functions
  void add(Light * light);
  void add(Primitive * primitive);
  void add(Shader * shader);

  // Raytracing functions
  Color traceRay(Ray * ray) const;
  virtual bool findIntersection(Ray * ray) const = 0;
  virtual bool findOcclusion(Ray * ray) const = 0;

protected:
  Color backgroundColor_;
  Texture environmentMap_;
  std::vector<Light*> lights_;
  std::vector<Primitive*> primitives_;
  std::vector<Shader*> shaders_;

};

#endif
