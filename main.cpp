#include "camera/perspectivecamera.h"
#include "scene/simplescene.h"

#include "light/ambientlight.h"
#include "light/directionallight.h"
#include "light/pointlight.h"

#include "primitive/objmodel.h"
#include "primitive/sphere.h"

#include "renderer/simplerenderer.h"

#include "shader/lambertshader.h"
#include "shader/materialshader.h"

int main() {
  // Set up the environment map scene
  SimpleScene scene;
  scene.setEnvironmentMap("C:/Users/A/Desktop/computergrafik-raytracing/data/space.ppm");

  // Set up the camera
  PerspectiveCamera camera;
  camera.setFovAngle(90);
  camera.setPosition(Vector3d(0,-3,10));
  camera.setForwardDirection(normalized(Vector3d(0,0.6,-1)));
  camera.setUpDirection(Vector3d(0,-1,0));

  // Materials
  MaterialShader * teapotMaterial = new MaterialShader(Color(1,0.6,0.6));
  teapotMaterial->setReflectance(0.5);
  scene.add(teapotMaterial);
  LambertShader * stadiumMaterial = new LambertShader(Color(0.6,0.8,1));
  scene.add(stadiumMaterial);

  // Load the Teapot and the Stadium
  ObjModel * teapot = new ObjModel(teapotMaterial);
  teapot->loadObj("C:/Users/A/Desktop/computergrafik-raytracing/data/teapot.obj",
                  Vector3d(1,1,1)*70, Vector3d(-0.5,-1,3),
                  ObjModel::NORMALS, ObjModel::SMOOTH);
  scene.add(teapot);

  ObjModel * stadium = new ObjModel(stadiumMaterial);
  stadium->loadObj("C:/Users/A/Desktop/computergrafik-raytracing/data/stadium.obj",
                   Vector3d(1,1,1)*70, Vector3d(-0.5,-1,3),
                   ObjModel::NORMALS, ObjModel::SMOOTH);
  scene.add(stadium);

  // Add some lights
  scene.add(new DirectionalLight(normalized(Vector3d(0.25,1.75,-0.5)), 5.f));
  scene.add(new AmbientLight(0.1));
  scene.add(new PointLight(Vector3d(4,5,6), 40));
  scene.add(new PointLight(Vector3d(-4,5,6), 20));

  // Render the scene
  SimpleRenderer renderer;
  //renderer.setSuperSamplingFactor(4);
  renderer.renderImage(scene, camera, 1920, 1080).save("result.ppm");

  return 0;
}

