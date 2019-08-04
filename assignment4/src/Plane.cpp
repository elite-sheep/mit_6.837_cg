/* Copyright 2019 The Microsoft Edge authors */

#include "Plane.h"

Plane::Plane(const Vector3f& normal,
    float d, Material* m): 
  Object3D(m),
  normal_(normal),
  d_(d) {}

bool Plane::intersect(const Ray &r, Hit& h, float tmin) {
  return false;
}
