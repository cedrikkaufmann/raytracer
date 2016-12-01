#include "camera/perspectivecamera.h"
#include "renderer/desaturationrenderer.h"
#include "renderer/depthrenderer.h"
#include "renderer/simplerenderer.h"
#include "renderer/hazerenderer.h"
#include "scene/simplescene.h"

#include "light/ambientlight.h"
#include "light/directionallight.h"
#include "light/pointlight.h"

#include "primitive/objmodel.h"
#include "primitive/sphere.h"

#include "shader/lambertshader.h"
#include "shader/phongshader.h"
#include "shader/brdfshader.h"

int main() {

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

  // Phong shader
  // Implement the phong shader and include the following:
  PhongShader * phongShader = new PhongShader(0.5, 0.5, 40, Color(0.8,0.3,1));
  scene.add(phongShader);
  scene.add(new Sphere(Vector3d(+12,0,20),5,phongShader));

  // BRDF shader
  // Implement the BRDF shader and include the following:
  //BrdfShader * goldBrdf = new BrdfShader("gold-paint.binary", Color(5, 5, 5));
  //BrdfShader * greenBrdf = new BrdfShader("green-acrylic.binary", Color(5, 5, 5));
  //scene.add(goldBrdf);
  //scene.add(greenBrdf);
  //scene.add(new Sphere(Vector3d(0,0,20),5,goldBrdf));
  //scene.add(new Sphere(Vector3d(-12,0,20),5,greenBrdf));

  // Add some lights
  scene.add(new PointLight(Vector3d(20,10,30),400));
  scene.add(new AmbientLight(0.1f));
  // This is a new type of light source that simulates sunlight:
  scene.add(new DirectionalLight(normalized(Vector3d(0.5,-0.5,-0.5)),0.5));


  // Load the terrain model
  ObjModel * terrain = new ObjModel(lambertWhite);
  terrain->loadObj("terrain1.obj",
                   Vector3d(1,1,1), Vector3d(0,-20,0),
                   ObjModel::TEXTURENORMALS, ObjModel::SMOOTH);
  scene.add(terrain);

  // Image size
  int const imageWidth = 512;
  int const imageHeight = 512;

  // Set up the renderer...
  SimpleRenderer renderer;
  // ... and render an image
  renderer.renderImage(scene, camera, imageWidth, imageHeight).save("result.ppm");

  // Implement this renderer and include the following:
  HazeRenderer hazeRenderer;
  hazeRenderer.setHazeColor(Color(0.25,0.75,1.0));
  hazeRenderer.setFalloff(0.0075);
  hazeRenderer.renderImage(scene, camera, imageWidth, imageHeight).save("result_hazed.ppm");

  // Implement this renderer and include the following:
  DesaturationRenderer desaturationRenderer;
  desaturationRenderer.setIntensity(0.75);
  desaturationRenderer.renderImage(scene, camera, imageWidth, imageHeight).save("result_desaturated.ppm");

  // Implement this renderer and include the following:
  DepthRenderer depthRenderer;
  depthRenderer.renderImage(scene, camera, imageWidth, imageHeight).save("result_depth.ppm");

  return 0;
}

