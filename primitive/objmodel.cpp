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
    if (strncmp(line, "v ", 2) == 0) {
        Vector3d vertex;
        int readValues = sscanf(line + 2, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

        if (readValues != 3){
            return false;
        }

        vData.push_back(vertex);
    }

    // Normals
    // IMPLEMENT ME!
    if (strncmp(line, "vn ", 3) == 0) {
        Vector3d normal;
        int readValues = sscanf(line + 3, "%f %f %f\n", &normal.x, &normal.y, &normal.z);

        if (readValues != 3){
            return false;
        }

        vnData.push_back(normal);
    }

    // Texture coordinates
    // IMPLEMENT ME!
    if (strncmp(line, "vt ", 3) == 0) {
        Vector2d uv;
        int readValues = sscanf(line + 3, "%f %f\n", &uv.u, &uv.v);

        if (readValues != 2){
            return false;
        }

        vtData.push_back(uv);
    }

    // Faces (TEXTURENORMALS, NORMALS, NONORMALS)
    if (strncmp(line, "f ", 2) == 0) {
      InputIndexData v, vn, vt;
      int readValues;
      switch (objStyle) {
      // TEXTURENORMALS
      // IMPLEMENT ME!
          case TEXTURENORMALS:
              readValues = sscanf(line + 2, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v.indexA, &vt.indexA, &vn.indexA,
                     &v.indexB, &vt.indexB, &vn.indexC, &v.indexC, &vt.indexC, &vn.indexC);

              if (readValues != 9){
                  return false;
              }

              vIndices.push_back(v);
              vnIndices.push_back(vn);
              vtIndices.push_back(vt);
              break;

      // NORMALS
      // IMPLEMENT ME!
          case NORMALS:
              readValues = sscanf(line + 2, "%d//%d %d//%d %d//%d\n", &v.indexA, &vn.indexA,
                     &v.indexB, &vn.indexC, &v.indexC, &vn.indexC);

              if (readValues != 6){
                  return false;
              }

              vIndices.push_back(v);
              vnIndices.push_back(vn);
              break;

      // NONORMALS
      // IMPLEMENT ME!
          case NONORMALS:
              readValues = sscanf(line + 2, "%d %d %d\n", &v.indexA, &v.indexB, &v.indexC);

              if (readValues != 3){
                  return false;
              }

              vIndices.push_back(v);
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
    /*
    triangleData[0].vertex = vData[vIndices[n].indexA - 1];
    triangleData[1].vertex = vData[vIndices[n].indexB - 1];
    triangleData[2].vertex = vData[vIndices[n].indexC - 1];
    */


    triangleData[0].vertex = componentProduct(vData[vIndices[n].indexA - 1], scale);
    triangleData[1].vertex = componentProduct(vData[vIndices[n].indexB - 1], scale);
    triangleData[2].vertex = componentProduct(vData[vIndices[n].indexC - 1], scale);


    // Load normals (if available)
    // IMPLEMENT ME!
    if (vnIndices.size() != 0) {
        triangleData[0].normal = vnData[vnIndices[n].indexA - 1];
        triangleData[1].normal = vnData[vnIndices[n].indexB - 1];
        triangleData[2].normal = vnData[vnIndices[n].indexC - 1];
    }

    // Load texture coordinates (if available)
    // IMPLEMENT ME!
    if (vnIndices.size() != 0) {
        triangleData[0].textureCoordinates = vtData[vtIndices[n].indexA - 1];
        triangleData[1].textureCoordinates = vtData[vtIndices[n].indexB - 1];
        triangleData[2].textureCoordinates = vtData[vtIndices[n].indexC - 1];
    }

    // Determine minBounds and maxBounds
    // IMPLEMENT ME!

    // Add the primitives
    // IMPLEMENT ME!
    Primitive * primitive;

    if (triangleStyle == STANDARD) {
        primitive = new Triangle(triangleData[0].vertex, triangleData[1].vertex, triangleData[2].vertex, shader());
    } else {
        // SmoothTriangle creation here
    }

    this->primitives.push_back(primitive);
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
