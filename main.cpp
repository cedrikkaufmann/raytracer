#include "camera/perspectivecamera.h"

#include "renderer/simplerenderer.h"
#include "scene/simplescene.h"

#include "primitive/infiniteplane.h"
#include "primitive/sphere.h"
#include "primitive/triangle.h"

#include "shader/flatshader.h"

int main() {
  // Set up the scene
  SimpleScene scene;
  scene.setBackgroundColor(Color(1,0.5,0));

  // Set up the camera
  PerspectiveCamera camera;
  camera.setPosition(Vector3d(0,5,-100));
  camera.setForwardDirection(Vector3d(0,0,1));
  camera.setUpDirection(Vector3d(0,1,0));
  camera.setFovAngle(50);

  // Create some materials
  FlatShader * whiteMaterial = new FlatShader(Color(1,1,1));
  FlatShader * blueMaterial = new FlatShader(Color(0,0,1));
  FlatShader * redMaterial = new FlatShader(Color(1,0,0));
  scene.add(whiteMaterial);
  scene.add(blueMaterial);
  scene.add(redMaterial);

  // Spheres
  scene.add(new Sphere(Vector3d(-30,10,70), 20, blueMaterial));
  scene.add(new Sphere(Vector3d(50,6,30), 50, whiteMaterial));

  // Add a few triangles
  scene.add(new Triangle(Vector3d(30,0,0), Vector3d(1, 2, 1), Vector3d(3, 2.8, -2), redMaterial));

  // Add a ground plane
  //scene.add(new InfinitePlane(Vector3d(0,30,0), Vector3d(0,1,0), redMaterial));


  // Set up the renderer...
  SimpleRenderer renderer;
  // ... and render an image
  Texture target = renderer.renderImage(scene, camera, 1280, 720);
  target.save("result.ppm");

  return 0;
}

