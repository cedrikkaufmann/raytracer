#include "camera/perspectivecamera.h"
#include "camera/omnidirectionalcamera.h"
#include "renderer/simplerenderer.h"
#include "renderer/depthoffieldrenderer.h"
#include "renderer/backgroundrenderer.h"
#include "scene/simplescene.h"

#include "light/ambientlight.h"
#include "light/pointlight.h"
#include "light/spotlight.h"
#include "light/directionallight.h"

#include "primitive/infiniteplane.h"
#include "primitive/objmodel.h"
#include "primitive/sphere.h"
#include "primitive/triangle.h"
#include "primitive/smoothtriangle.h"

#include "shader/lambertshader.h"
#include "shader/toonshader.h"
#include "shader/phongshader.h"

#include <iostream>
#include <omp.h>

int main() {
  std::cout << "RayTracing Engine - OpenMP SSE Version" << std::endl << "Threads beeing used: " << omp_get_max_threads() << std::endl << std::endl;

  // Set up the scene
  SimpleScene scene;
  scene.setBackgroundColor(Color(0,0,0));

  // Set up the camera
  PerspectiveCamera camera;
  camera.setPosition(Vector3d(0,5,50));
  camera.setForwardDirection(normalized(Vector3d(0,-0.5,-1)));
  camera.setUpDirection(Vector3d(0,-1,0));
  camera.setFovAngle(80);

  // Lambert shader
  LambertShader * lambertWhite = new LambertShader(Color(1,1,1));
  scene.add(lambertWhite);

  // BRDF shader
  // Implement the BRDF shader and include the following:
  ToonShader * blueToon = new ToonShader(3, 0.3f, 0.85f, 0.45f, 0.3f, 0.7f, Color(0.6,0.8,1));
  ToonShader * greenToon = new ToonShader(7, 0.35f, 0.9f, 0.7f, 1, 1, Color(0.4,0.9,0.4));
  ToonShader * redToon = new ToonShader(5, 0.25f, 0.8f, 0.3f, 0.6f, 0.7f, Color(1,0.6,0.6));
  scene.add(blueToon);
  scene.add(greenToon);
  scene.add(redToon);
  scene.add(new Sphere(Vector3d(0,0,20),5,blueToon));
  scene.add(new Sphere(Vector3d(-7,0,30),5,greenToon));
  scene.add(new Sphere(Vector3d(+12,0,12),5,redToon));

  // Add some lights
  //scene.add(new PointLight(Vector3d(20,10,30),400));
  //scene.add(new AmbientLight(0.1f));
  // This is a new type of light source that simulates sunlight:
  scene.add(new DirectionalLight(normalized(Vector3d(0.5,-0.5,-0.5)),0.7));


  // Load the terrain model
  ObjModel * terrain = new ObjModel(lambertWhite);
  terrain->loadObj("data/terrain1.obj",
                   Vector3d(1,1,1), Vector3d(0,-20,0),
                   ObjModel::TEXTURENORMALS, ObjModel::SMOOTH);
  scene.add(terrain);

  // Set up the renderer...
  DepthOfFieldRenderer renderer;
  renderer.setApertureRadius(2.8f);
  renderer.setApertureRays(50);
  renderer.setFocalDistance(40);
  // ... and render an image
  renderer.renderImage(scene, camera, 2000, 2000).save("result.ppm");

  return 0;
}
