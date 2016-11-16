#include "camera/perspectivecamera.h"
#include "renderer/simplerenderer.h"
#include "scene/simplescene.h"

#include "light/pointlight.h"

#include "primitive/sphere.h"
#include "primitive/triangle.h"

#include "shader/simpleshadowshader.h"
#include "shader/mirrorshader.h"
#include "shader/refractionshader.h"
#include "shader/lambertshader.h"

int main() {
  // Set up the scene
  SimpleScene scene;

  // Environment map
  Texture environment("environment.ppm");
  scene.setEnvironmentMap(environment);

  // Set up the camera
  PerspectiveCamera camera;
  camera.setPosition(Vector3d(0,0,-60));
  camera.setForwardDirection(Vector3d(0,0,1));
  camera.setUpDirection(Vector3d(0,1,0));
  camera.setFovAngle(90);

  // Add some lights
  scene.add(new PointLight(Vector3d(20,10,-50), 450.f, Color(1,1,1)));

  // Create some materials
  LambertShader * lambert = new LambertShader(Color(0,0,1));
  MirrorShader * mirror = new MirrorShader();
  RefractionShader * refraction = new RefractionShader(0.4, 0.4, 2.4);
  SimpleShadowShader * shadow = new SimpleShadowShader(Color(1,0,0));
  scene.add(lambert);
  scene.add(shadow);
  scene.add(mirror);
  scene.add(refraction);

  // Primitives
  scene.add(new Sphere(Vector3d(-10,-3,-30), 10, lambert)); // lambert
  scene.add(new Sphere(Vector3d(-20,-20,100), 25, mirror)); // mirror
  scene.add(new Sphere(Vector3d(0,0,0), 25, refraction)); // refraction
  scene.add(new Triangle(Vector3d(-5,-1,-40), Vector3d(0, 2, -40), Vector3d(-2, 6, -40), shadow));

  // Set up the renderer...
  SimpleRenderer renderer;
  // ... and render an image
  Texture target = renderer.renderImage(scene, camera, 1280, 720);
  target.save("result.ppm");

  return 0;
}

