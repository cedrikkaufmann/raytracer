#include <cassert>
#include <cmath>
#include <cstdio>
#include "scene/scene.h"
#include "light/light.h"
#include "primitive/primitive.h"
#include "shader/shader.h"

Scene::~Scene() {
  for (unsigned int i = 0; i < this->lights_.size(); ++i)
    delete this->lights_[i];
  for (unsigned int i = 0; i < this->primitives_.size(); ++i)
    delete this->primitives_[i];
  for (unsigned int i = 0; i < this->shaders_.size(); ++i)
    delete this->shaders_[i];
}

void Scene::add(Light * light) {
  light->parentScene_ = this;
  this->lights_.push_back(light);
}

void Scene::add(Primitive * primitive) {
  assert(primitive->shader());
  this->primitives_.push_back(primitive);
}

void Scene::add(Shader * shader) {
  shader->parentScene_ = this;
  this->shaders_.push_back(shader);
}

Color Scene::traceRay(Ray * ray) const {
  if (this->findIntersection(ray) && ray->remainingBounces-- > 0) {

    // If the ray has hit an object, call the shader ...
    return ray->primitive->shader()->shade(ray);
  } else if (!this->environmentMap_.isNull()) {

    // ... otherwise look up the environment map ...

    float phi = std::acos(ray->direction.y * -1);
    float theta = std::atan2(ray->direction.z, ray->direction.x);

    float v = (phi / PI);
    float u = ((theta + PI) / (2 * PI));

    return environmentMap_.color(u, v);

  } else {

    // ... if all else fails, just return the background color
    return this->backgroundColor_;

  }
}
