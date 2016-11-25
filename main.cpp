#include "camera/perspectivecamera.h"
#include "renderer/simplerenderer.h"
#include "scene/simplescene.h"

#include "light/ambientlight.h"
#include "light/pointlight.h"
#include "light/spotlight.h"

#include "primitive/infiniteplane.h"
#include "primitive/objmodel.h"
#include "primitive/sphere.h"
#include "primitive/triangle.h"
#include "primitive/smoothtriangle.h"

#include "shader/flatshader.h"
#include "shader/simpleshadowshader.h"
#include "shader/mirrorshader.h"
#include "shader/refractionshader.h"
#include "shader/lambertshader.h"

int main() {

  SimpleScene scene;
  scene.setBackgroundColor(Color(0,0,0));

  PerspectiveCamera camera;
  camera.setPosition(Vector3d(0,0,10));
  camera.setForwardDirection(Vector3d(0,0,-1));
  camera.setUpDirection(Vector3d(0,-1,0));
  camera.setFovAngle(80);

  // Create some materials
  LambertShader * lambertWhite = new LambertShader(Color(1,1,1));
  LambertShader * lambertRed = new LambertShader(Color(1,0.6,0.6));
  LambertShader * lambertBlue = new LambertShader(Color(0.6,0.8,1));
  LambertShader * lambertGreen = new LambertShader(Color(0.4,0.9,0.4));
  LambertShader * lambertYellow = new LambertShader(Color(1,0.9,0.1));
  LambertShader * LambertBrown = new LambertShader(Color(0.8,0.4,0.3));

  scene.add(lambertWhite);
  scene.add(lambertRed);
  scene.add(lambertBlue);
  scene.add(lambertGreen);
  scene.add(lambertYellow);
  scene.add(LambertBrown);


  // Lets build a Cornell Box
  scene.add(new InfinitePlane(Vector3d(0,0,-10),Vector3d(0,0,+1),lambertWhite));
  scene.add(new InfinitePlane(Vector3d(0,-10,0),Vector3d(0,+1,0),lambertWhite));
  scene.add(new InfinitePlane(Vector3d(0,+10,0),Vector3d(0,-1,0),lambertWhite));
  scene.add(new InfinitePlane(Vector3d(-10,0,0),Vector3d(+1,0,0),lambertRed));
  scene.add(new InfinitePlane(Vector3d(+10,0,0),Vector3d(-1,0,0),lambertBlue));



  // Add some lights
  scene.add(new PointLight(Vector3d(0, 9, 0),50 ,Color(1,0.9,0.5)));
  // Once you have implemented the spotlight, uncomment this section

  scene.add(new SpotLight(Vector3d(-4, 4, 10),      // Position
                          Vector3d(0.3,-0.3,-0.9),  // Direction
                          15.0f,                    // Minimum alpha
                          30.0f,                    // Maximum alpha
                          450,                      // Intensity
                          Color(1,1,1)              // Color
                          )
            );

  // Once you have implemented the ambientlight, use this line
  //scene.add(new AmbientLight(0.25f));

  // Add a cone
  Vector3d const top(4,2,0);
  Vector3d const topNormal(0,1,0);
  float const height = 5;
  float const radius = 3;
  int const tesselation = 16;
  Vector3d const center(top.x, top.y - height, top.z);
  for (int i = 0; i < tesselation; ++i) {
    Vector3d const a(center.x + radius*std::cos(i*(2.0f*PI/tesselation)),
                     center.y,
                     center.z + radius*std::sin(i*(2.0f*PI/tesselation)));
    Vector3d const b(center.x + radius*std::cos((i+1)*(2.0f*PI/tesselation)),
                     center.y,
                     center.z + radius*std::sin((i+1)*(2.0f*PI/tesselation)));
    scene.add(new Triangle(top, a, b, lambertYellow));
    // Once you have implemented the SmoothTriangle, use this line
    scene.add(new SmoothTriangle(top, a, b, topNormal, normalized(a-center), normalized(b-center), lambertYellow));
  }


  // Load the cow model
  ObjModel * cow = new ObjModel(LambertBrown);
  cow->loadObj("cow.obj",
               Vector3d(1,1,1)*60, Vector3d(0,-1,0),
               ObjModel::NONORMALS, ObjModel::STANDARD);
  scene.add(cow);


  // Set up the renderer...
  SimpleRenderer renderer;
  // ... and render an image
  Texture target = renderer.renderImage(scene, camera, 200, 200);
  target.save("result.ppm");

  return 0;
}

