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
#include "shader/mirrorshader.h"
#include "shader/materialshader.h"
#include "shader/brdfshader.h"

#include <iostream>
#include <omp.h>

int main() {
  std::cout << "RayTracing Engine - OpenMP SSE Version" << std::endl << "Threads beeing used: " << omp_get_max_threads() << std::endl << std::endl;

  // Set up the scene
  SimpleScene scene;
  scene.setEnvironmentMap(Texture("data/sky_stars_night_bg.jpg"));
  scene.setBackgroundColor(Color(0,0,0));

  // Set up the camera
  PerspectiveCamera camera;
  camera.setPosition(Vector3d(0,5,250));
  camera.setForwardDirection(normalized(Vector3d(0,-0.5,-1)));
  camera.setUpDirection(Vector3d(0,-1.6f,.2f));
  camera.setFovAngle(90);

  // Set up shaders
  MirrorShader * mirrorShader = new MirrorShader();
  scene.add(mirrorShader);

  MaterialShader * alphaShader = new MaterialShader();
  alphaShader->setOpacity(0.2f);
  scene.add(alphaShader);

  LambertShader * lambertGreen = new LambertShader(Color(0.4,0.9,0.4));
  scene.add(lambertGreen);

  ToonShader * toonRed = new ToonShader(6, 0.3f, 0.9f, 0.4f, 1, 1, Color(1,0.6,0.6));
  ToonShader * toonBlue = new ToonShader(6, 0.3f, 0.9f, 0.4f, 1, 1, Color(0.6,0.8,1));
  ToonShader * toonGreen = new ToonShader(6, 0.3f, 0.9f, 0.4f, 1, 1, Color(0.4,0.9,0.4));
  ToonShader * toonYellow = new ToonShader(6, 0.3f, 0.9f, 0.4f, 1, 1, Color(1,0.9,0.1));
  scene.add(toonRed);
  scene.add(toonBlue);
  scene.add(toonGreen);
  scene.add(toonYellow);

  // Set up terrain
  Texture mountainDiffuse("data/mountain/color.tif");
  Texture mountainNormal("data/mountain/normal.tif");
  MaterialShader * mountainShader = new MaterialShader();
  mountainShader->setDiffuseMap(mountainDiffuse);
  mountainShader->setDiffuseCoefficient(0.7f);
  mountainShader->setNormalMap(mountainNormal);
  mountainShader->setNormalCoefficient(0.8f);
  scene.add(mountainShader);

  ObjModel * mountain = new ObjModel(mountainShader);
  mountain->loadObj("data/mountain/terrain.obj",
                   Vector3d(1,1,1), Vector3d(23,-20,0),
                   ObjModel::TEXTURENORMALS, ObjModel::TEXTURED);
  scene.add(mountain);


  // Set up abstract tables
  ObjModel * abstractTable1 = new ObjModel(mirrorShader);
  abstractTable1->loadObj("data/table_abstract.obj",
                         Vector3d(1,1,1)*20, Vector3d(40,-60,100),
                         ObjModel::TEXTURENORMALS, ObjModel::SMOOTH);
  scene.add(abstractTable1);


  ObjModel * abstractTable2 = new ObjModel(mirrorShader);
  abstractTable2->loadObj("data/table_abstract.obj",
                         Vector3d(1,1,1)*20, Vector3d(-250,-60,-210),
                         ObjModel::TEXTURENORMALS, ObjModel::SMOOTH);
  scene.add(abstractTable2);


  ObjModel * abstractTable3 = new ObjModel(mirrorShader);
  abstractTable3->loadObj("data/table_abstract.obj",
                         Vector3d(1,1,1)*5, Vector3d(-50,-60,200),
                         ObjModel::TEXTURENORMALS, ObjModel::SMOOTH);
  scene.add(abstractTable3);

  // Set up toon speheres
  scene.add(new Sphere(Vector3d(-20,-60,60),20,toonRed));
  scene.add(new Sphere(Vector3d(-7,0,-20),50,toonBlue));
  scene.add(new Sphere(Vector3d(-200,-60,-250),30,toonGreen));
  scene.add(new Sphere(Vector3d(30,-60,240),30,toonYellow));

  // Add lights
  scene.add(new DirectionalLight(normalized(Vector3d(-0.5,-0.4,0.4)), 2.f));
  scene.add(new AmbientLight(0.25));


  // Set up the renderer...
  DepthOfFieldRenderer renderer;
  renderer.setApertureRadius(0.7f);
  renderer.setApertureRays(25);
  renderer.setFocalDistance(100);

  // ... and render an image
  renderer.renderImage(scene, camera, 2000, 2000).save("result.ppm");

  return 0;
}
