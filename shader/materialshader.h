#ifndef MATERIALSHADER_H
#define MATERIALSHADER_H

#include "shader/shader.h"
#include "common/texture.h"

class MaterialShader : public Shader {

public:
  // Constructor
  MaterialShader(Color const& objectColor = Color(1,1,1));

  // Set
  void setAlphaMap(Texture const& alphaMap) {
    this->alphaMap = alphaMap;
  }
  void setOpacity(float opacity) {
    this->opacity = opacity;
  }
  void setNormalMap(Texture const& normalMap) {
    this->normalMap = normalMap;
  }
  void setNormalCoefficient(float normalCoefficient) {
    this->normalCoefficient = normalCoefficient;
  }
  void setDiffuseMap(Texture const& diffuseMap) {
    this->diffuseMap = diffuseMap;
  }
  void setDiffuseCoefficient(float diffuseCoefficient) {
    this->diffuseCoefficient = diffuseCoefficient;
  }
  void setSpecularMap(Texture const& specularMap) {
    this->specularMap = specularMap;
  }
  void setSpecularCoefficient(float specularCoefficient) {
    this->specularCoefficient = specularCoefficient;
  }
  void setShininessExponent(float shininessExponent) {
    this->shininessExponent = shininessExponent;
  }
  void setReflectionMap(Texture const& reflectionMap) {
    this->reflectionMap = reflectionMap;
  }

  // Shader functions
  virtual Color shade(Ray * ray) const;
  virtual bool isTransparent() const;

private:
  Color objectColor;

  Texture alphaMap;
  float opacity;

  Texture normalMap;
  float normalCoefficient;

  Texture diffuseMap;
  float diffuseCoefficient;

  Texture reflectionMap;

  Texture specularMap;
  float specularCoefficient;
  float shininessExponent;

};

#endif
