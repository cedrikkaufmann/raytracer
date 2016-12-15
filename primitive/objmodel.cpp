#include <cstdio>
#include <cstring>
#include "primitive/objmodel.h"
#include "primitive/smoothtriangle.h"
#include "primitive/texturedtriangle.h"
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
    if (strncmp(line, "v ", 2) == 0) {
      float a, b, c;
      sscanf(line, "v %f %f %f", &a, &b, &c);
      vData.push_back(Vector3d(a,b,c));
    }

    // Normals
    if (strncmp(line, "vn ", 3) == 0) {
      float a, b, c;
      sscanf(line, "vn %f %f %f", &a, &b, &c);
      vnData.push_back(normalized(Vector3d(a,b,c)));
    }

    // Texture coordinates
    if (strncmp(line, "vt ", 2) == 0) {
      float u, v;
      sscanf(line, "vt %f %f", &u, &v);
      vtData.push_back(Vector2d(u,v));
    }

    // Faces
    if (strncmp(line, "f ", 2) == 0) {
      InputIndexData v, vn, vt;
      switch (objStyle) {

      case TEXTURENORMALS:
        sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
               &v.indexA, &vn.indexA, &vt.indexA,
               &v.indexB, &vn.indexB, &vt.indexB,
               &v.indexC, &vn.indexC, &vt.indexC);
        vIndices.push_back({v.indexA-1, v.indexB-1, v.indexC-1});
        vnIndices.push_back({vn.indexA-1, vn.indexB-1, vn.indexC-1});
        vtIndices.push_back({vt.indexA-1, vt.indexB-1, vt.indexC-1});
        break;

      case NORMALS:
        sscanf(line, "f %d/%d %d/%d %d/%d",
               &v.indexA, &vn.indexA,
               &v.indexB, &vn.indexB,
               &v.indexC, &vn.indexC);
        vIndices.push_back({v.indexA-1, v.indexB-1, v.indexC-1});
        vnIndices.push_back({vn.indexA-1, vn.indexB-1, vn.indexC-1});
        break;

      case NONORMALS:
        sscanf(line, "f %d %d %d",
               &v.indexA, &v.indexB, &v.indexC);
        vIndices.push_back({v.indexA-1, v.indexB-1, v.indexC-1});
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
    triangleData[0].vertex = componentProduct(vData[vIndices[n].indexA], scale) + translation;
    triangleData[1].vertex = componentProduct(vData[vIndices[n].indexB], scale) + translation;
    triangleData[2].vertex = componentProduct(vData[vIndices[n].indexC], scale) + translation;

    // Load normals (if available)
    if ((objStyle == NORMALS) || (objStyle == TEXTURENORMALS)) {
      triangleData[0].normal = vnData[vnIndices[n].indexA];
      triangleData[1].normal = vnData[vnIndices[n].indexB];
      triangleData[2].normal = vnData[vnIndices[n].indexC];
    }

    // Load texture coordinates (if available)
    if (objStyle == TEXTURENORMALS) {
      triangleData[0].textureCoordinates = vtData[vtIndices[n].indexA];
      triangleData[1].textureCoordinates = vtData[vtIndices[n].indexB];
      triangleData[2].textureCoordinates = vtData[vtIndices[n].indexC];
    }

    // Determine minBounds and maxBounds
    for (unsigned int k = 0; k < 3; ++k) {
      this->minBounds.x = std::min(this->minBounds.x, triangleData[k].vertex.x);
      this->minBounds.y = std::min(this->minBounds.y, triangleData[k].vertex.y);
      this->minBounds.z = std::min(this->minBounds.z, triangleData[k].vertex.z);
      this->maxBounds.x = std::max(this->maxBounds.x, triangleData[k].vertex.x);
      this->maxBounds.y = std::max(this->maxBounds.y, triangleData[k].vertex.y);
      this->maxBounds.z = std::max(this->maxBounds.z, triangleData[k].vertex.z);
    }

    // Add the primitives
    switch (triangleStyle) {
    case STANDARD:
      this->primitives.push_back(new Triangle(triangleData[0].vertex, triangleData[1].vertex, triangleData[2].vertex, this->shader()));
      break;
    case SMOOTH:
      this->primitives.push_back(new SmoothTriangle(triangleData[0].vertex, triangleData[1].vertex, triangleData[2].vertex,
          triangleData[0].normal, triangleData[1].normal, triangleData[2].normal, this->shader()));
      break;
    case TEXTURED:
      this->primitives.push_back(new TexturedTriangle(triangleData[0].vertex, triangleData[1].vertex, triangleData[2].vertex,
                triangleData[0].normal, triangleData[1].normal, triangleData[2].normal,
                triangleData[0].textureCoordinates, triangleData[1].textureCoordinates, triangleData[2].textureCoordinates,
                this->shader()));
    }

  }
  printf("(ObjModel): %lu primitives added\n", this->primitives.size());
  return true;
}

bool ObjModel::intersect(Ray * ray) const {
  // Ray box intersection
  bool hit = false;

  BoundingBox box(this->minBounds, this->maxBounds);

  if (box.intersects(*ray)) {
      for (unsigned int i = 0; i < this->primitives.size(); ++i) {
        hit |= this->primitives[i]->intersect(ray);
      }
      return hit;
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
  return this->minBounds[dimension];
}

float ObjModel::maximumBounds(int dimension) const {
  return this->maxBounds[dimension];
}
