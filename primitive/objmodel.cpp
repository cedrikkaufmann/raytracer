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
    if (strncmp(line, "v ", 2) == 0) {
        Vector3d vertex;
        int readValues = sscanf(line + 2, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

        if (readValues != 3){
            return false;
        }

        vData.push_back(vertex);
    }

    // Normals
    if (strncmp(line, "vn ", 3) == 0) {
        Vector3d normal;
        int readValues = sscanf(line + 3, "%f %f %f\n", &normal.x, &normal.y, &normal.z);

        if (readValues != 3){
            return false;
        }

        vnData.push_back(normal);
    }

    // Texture coordinates
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
    triangleData[0].vertex = componentProduct(vData[vIndices[n].indexA - 1], scale) + translation;
    triangleData[1].vertex = componentProduct(vData[vIndices[n].indexB - 1], scale) + translation;
    triangleData[2].vertex = componentProduct(vData[vIndices[n].indexC - 1], scale) + translation;


    // Load normals (if available)
    if (vnIndices.size() != 0) {
        triangleData[0].normal = componentProduct(vnData[vnIndices[n].indexA - 1], scale) + translation;
        triangleData[1].normal = componentProduct(vnData[vnIndices[n].indexB - 1], scale) + translation;
        triangleData[2].normal = componentProduct(vnData[vnIndices[n].indexC - 1], scale) + translation;
        normalize(&triangleData[0].normal);
        normalize(&triangleData[1].normal);
        normalize(&triangleData[2].normal);
    }

    // Load texture coordinates (if available)
    if (vtIndices.size() != 0) {
        triangleData[0].textureCoordinates = componentProduct(vtData[vtIndices[n].indexA - 1], Vector2d(scale.x, scale.y)) + Vector2d(translation.x, translation.y);
        triangleData[1].textureCoordinates = componentProduct(vtData[vtIndices[n].indexB - 1], Vector2d(scale.x, scale.y)) + Vector2d(translation.x, translation.y);
        triangleData[2].textureCoordinates = componentProduct(vtData[vtIndices[n].indexC - 1], Vector2d(scale.x, scale.y)) + Vector2d(translation.x, translation.y);
    }

    // Determine minBounds and maxBounds
    for (unsigned int i = 0; i < 3; ++i) {
        if (triangleData[i].vertex.x < minBounds.x) {
          minBounds.x = triangleData[i].vertex.x;
        }
        if (triangleData[i].vertex.y < minBounds.y) {
          minBounds.y = triangleData[i].vertex.y;
        }
        if (triangleData[i].vertex.z < minBounds.z) {
          minBounds.z = triangleData[i].vertex.z;
        }

        if (triangleData[i].vertex.x > maxBounds.x) {
          maxBounds.x = triangleData[i].vertex.x;
        }
        if (triangleData[i].vertex.y > maxBounds.y) {
          maxBounds.y = triangleData[i].vertex.y;
        }
        if (triangleData[i].vertex.z > maxBounds.z) {
          maxBounds.z = triangleData[i].vertex.z;
        }
    }

    // Add the primitives
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
  bool hit = true;

  //Using Smit's algorithm
  Vector3d invDirection(1 / ray->direction.x, 1 / ray->direction.y, 1 / ray->direction.z);

  Vector3d bounds[2];
  bounds[0] = minBounds;
  bounds[1] = maxBounds;

  int sign[3];
  sign[0] = (invDirection.x < 0);
  sign[1] = (invDirection.y < 0);
  sign[2] = (invDirection.z < 0);

  float tmin, tmax, tymin, tymax, tzmin, tzmax;

  tmin = (bounds[sign[0]].x - ray->origin.x) * invDirection.x;
  tmax = (bounds[1-sign[0]].x - ray->origin.x) * invDirection.x;
  tymin = (bounds[sign[1]].y - ray->origin.y) * invDirection.y;
  tymax = (bounds[1-sign[1]].y - ray->origin.y) * invDirection.y;

  if ( (tmin > tymax) || (tymin > tmax) )
    return false;
  if (tymin > tmin)
    tmin = tymin;
  if (tymax < tmax)
    tmax = tymax;

  tzmin = (bounds[sign[2]].z - ray->origin.z) * invDirection.z;
  tzmax = (bounds[1-sign[2]].z - ray->origin.z) * invDirection.z;

  if ( (tmin > tzmax) || (tzmin > tmax) )
    return false;
  if (tzmin > tmin)
    tmin = tzmin;
  if (tzmax < tmax)
    tmax = tzmax;

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
