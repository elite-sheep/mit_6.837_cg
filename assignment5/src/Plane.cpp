/* Copyright 2019 The Microsoft Edge authors */

#include "Plane.h"

Plane::Plane(const Vector3f& normal,
    float d, Material* m): 
  Object3D(m),
  normal_(normal),
  d_(-d) {}

bool Plane::intersect(const Ray &r, Hit& h, float tmin) {
  float d1 = Vector3f::dot(normal_, r.getOrigin());
  float d2 = Vector3f::dot(r.getDirection(), normal_);
  float t = -(d_ + d1) / d2;

  if (t >= tmin && h.getT() > t) {
    h.set(t, material, normal_.normalized());
    return true;
  }

  return false;
}
