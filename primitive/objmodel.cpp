#include <cstdio>
#include <cstring>
#include "primitive/objmodel.h"
#include "primitive/smoothtriangle.h"
#include "primitive/triangle.h"

// A small struct to help us organize the index data
struct InputIndexData {
  int indexA, indexB, indexC;
};

ObjModel::ObjModel(Shader * shader)
  : Primitive(shader),
    minBounds(Vector3d(+INFINITY,+INFINITY,+INFINITY)),
    maxBounds(Vector3d(-INFINITY,-INFINITY,-INFINITY)) {}

bool ObjModel::loadObj(char const* fileName,
                       Vector3d const& scale, Vector3d const& translation,
                       ObjStyle objStyle, TriangleStyle triangleStyle) {

  // Open file from disk
  FILE * file = fopen(fileName, "r");
  if (!file) {
    printf("(ObjModel): Could not open .obj file: %s\n", fileName);
    return false;
  }

  // Obj index data
  std::vector<InputIndexData> vIndices;
  std::vector<InputIndexData> vnIndices;
  std::vector<InputIndexData> vtIndices;

  // Actual model data
  std::vector<Vector3d> vData;
  std::vector<Vector3d> vnData;
  std::vector<Vector2d> vtData;

  // Read vertices, normals, textures, and faces from the file
  char line[1000];
  while (fgets(line, 1000, file) && !feof(file)) {

    // Vertices
    // IMPLEMENT ME!

    // Normals
    // IMPLEMENT ME!

    // Texture coordinates
    // IMPLEMENT ME!

    // Faces (TEXTURENORMALS, NORMALS, NONORMALS)
    if (strncmp(line, "f ", 2) == 0) {
      InputIndexData v, vn, vt;
      switch (objStyle) {

      // TEXTURENORMALS
      // IMPLEMENT ME!
          case TEXTURENORMALS:

              break;

      // NORMALS
      // IMPLEMENT ME!
          case NORMALS:

              break;

      // NONORMALS
      // IMPLEMENT ME!
          case NONORMALS:

              break;

      }
    }
  }
  printf("(ObjModel): %lu faces parsed\n", vIndices.size());

  // For each face, add the corresponding triangle primitive
  for (unsigned int n = 0; n < vIndices.size(); ++n) {

    // Vertex positions of vertices, normals, texture coords
    struct {
      Vector3d vertex;
      Vector3d normal;
      Vector2d textureCoordinates;
    } triangleData[3];

    // Load vertices
    // IMPLEMENT ME!


    // Load normals (if available)
    // IMPLEMENT ME!


    // Load texture coordinates (if available)
    // IMPLEMENT ME!


    // Determine minBounds and maxBounds
    // IMPLEMENT ME!


    // Add the primitives
    // IMPLEMENT ME!


  }
  printf("(ObjModel): %lu primitives added\n", this->primitives.size());
  return true;
}

bool ObjModel::intersect(Ray * ray) const {
  // Ray box intersection
  bool hit = false;
  for (unsigned int i = 0; i < this->primitives.size(); ++i) {
    hit |= this->primitives[i]->intersect(ray);
  }
  return hit;
}

Vector3d ObjModel::normalFromRay(Ray const& ray) const {
  // This function should never be called as all requests should go
  // to the individual triangles in the mesh.
  (void)ray; // ray is unused in this case, but we do not want a warning.
  return Vector3d();
}

float ObjModel::minimumBounds(int dimension) const {
  /*
    * IMPLEMENT ME!
    *
    * These values are used for determining the bounding box.
    * This should return the minimum value along the given dimension.
    *
    */
  return -INFINITY;
}

float ObjModel::maximumBounds(int dimension) const {
  /*
    * IMPLEMENT ME!
    *
    * These values are used for determining the bounding box.
    * This should return the minimum value along the given dimension.
    *
    */
  return +INFINITY;
}
