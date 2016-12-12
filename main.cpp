#include "camera/perspectivecamera.h"
#include "camera/omnidirectionalcamera.h"
#include "renderer/backgroundrenderer.h"
#include "renderer/simplerenderer.h"
#include "scene/simplescene.h"

#include "light/ambientlight.h"
#include "light/directionallight.h"
#include "light/pointlight.h"

#include "primitive/objmodel.h"
#include "primitive/sphere.h"

#include "shader/materialshader.h"

int main() {

  // Set up the environment map scene
  SimpleScene backgroundScene;
  backgroundScene.setEnvironmentMap("data/space.ppm");

  // Set up the omnidirectional camera
  OmnidirectionalCamera backgroundCamera;
  backgroundCamera.setPosition(Vector3d(60,0,0));

  // Add Mars
  Texture marsDiffuse("data/mars_diffuse.ppm");
  Texture marsNormal("data/mars_normal.ppm");
  MaterialShader * marsShader = new MaterialShader;
  marsShader->setDiffuseMap(marsDiffuse);
  marsShader->setDiffuseCoefficient(0.5f);
  marsShader->setNormalMap(marsNormal);
  backgroundScene.add(marsShader);
  backgroundScene.add(new Sphere(Vector3d(0,20,0), 35, marsShader));

  // Add a Moon
  Texture moonDiffuse("data/moon_diffuse.ppm");
  Texture moonNormal("data/moon_normal.ppm");
  MaterialShader * moonShader = new MaterialShader;
  moonShader->setDiffuseMap(moonDiffuse);
  moonShader->setDiffuseCoefficient(0.5f);
  moonShader->setNormalMap(moonNormal);
  backgroundScene.add(moonShader);
  backgroundScene.add(new Sphere(Vector3d(100,0,0), 15, moonShader));

  // Add some lights
  backgroundScene.add(new DirectionalLight(normalized(Vector3d(0.2,0,1)), 3.f));
  backgroundScene.add(new AmbientLight(0.5));

  // Render the background
  // The BackgroundRenderer is a specialized renderer. It is not much different
  // from the simple renderer, but it ignores aspect ratio and does not center the image
  BackgroundRenderer environmentRenderer;
  Texture environmentMap = environmentRenderer.renderImage(backgroundScene, backgroundCamera, 2048, 1024);
  environmentMap.save("environment.ppm");


  ////////////////////////////////////////////////////////////////////////////


  // Set up the actual scene
  SimpleScene scene;
  scene.setEnvironmentMap(environmentMap);

  // Set up the camera
  PerspectiveCamera camera;
  camera.setForwardDirection(normalized(Vector3d(-1,-0.15,0.6)));
  camera.setUpDirection(normalized(Vector3d(0,-1,0)));
  camera.setFovAngle(90);

  // Add the earth
  Texture earthDiffuse("data/earth_diffuse.ppm");
  Texture earthSpecular("data/earth_specular.ppm");
  Texture earthNormal("data/earth_normal.ppm");
  Texture earthClouds("data/earth_clouds.ppm");
  MaterialShader * earthCloudShader = new MaterialShader(Color(1,1,1));
  earthCloudShader->setAlphaMap(earthClouds);
  scene.add(earthCloudShader);
  MaterialShader * earthShader = new MaterialShader;
  earthShader->setDiffuseMap(earthDiffuse);
  earthShader->setDiffuseCoefficient(0.5f);
  earthShader->setSpecularMap(earthSpecular);
  earthShader->setSpecularCoefficient(0.5f);
  earthShader->setShininessExponent(15);
  earthShader->setNormalMap(earthNormal);
  scene.add(earthShader);
  scene.add(new Sphere(Vector3d(-50,0,60), 20, earthShader));
  scene.add(new Sphere(Vector3d(-50,0,60), 20.05, earthCloudShader));

  // Add the spaceship
  Texture spaceshipDiffuse("data/space_frigate_6_diffuse.ppm");
  Texture spaceshipSpecular("data/space_frigate_6_specular.ppm");
  Texture spaceshipNormal("data/space_frigate_6_normal.ppm");
  Texture spaceshipReflection("data/space_frigate_6_specular.ppm");
  MaterialShader * spaceshipShader = new MaterialShader;
  spaceshipShader->setDiffuseMap(spaceshipDiffuse);
  spaceshipShader->setDiffuseCoefficient(0.5f);
  spaceshipShader->setSpecularMap(spaceshipSpecular);
  spaceshipShader->setNormalMap(spaceshipNormal);
  spaceshipShader->setNormalCoefficient(0.8f);
  spaceshipShader->setSpecularCoefficient(1);
  spaceshipShader->setShininessExponent(40);
  spaceshipShader->setReflectionMap(spaceshipReflection);
  scene.add(spaceshipShader);

  // IMPLEMENT ME!
  // Implement the TexturedTriangle and add it to the ObjModel,
  // then uncomment the following code to add the spaceship:

  /* ObjModel * spaceship = new ObjModel(spaceshipShader);
  spaceship->loadObj("data/space_frigate_6.obj",
                  Vector3d(-1,1,1)/20, Vector3d(-1.3,-0.3,0.7),
                  ObjModel::TEXTURENORMALS, ObjModel::TEXTURED);
  scene.add(spaceship); */

  // Add some lights
  scene.add(new DirectionalLight(normalized(Vector3d(-0.8,-0.4,0.4)), 2.f));
  scene.add(new AmbientLight(0.25));

  // Render the scene
  SimpleRenderer renderer;
  renderer.renderImage(scene, camera, 1024, 768).save("result.ppm");

  return 0;
}

