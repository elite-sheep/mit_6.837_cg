/*************************************************************************
    > File Name: src/Transform.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: 2019年08月11日 星期日 18时16分41秒
 ************************************************************************/

#include "Transform.h"

#include "Hit.h"

Transform::Transform(const Matrix4f& m, Object3D* obj) :
  o(obj),
  transform(m) {}

bool Transform::intersect(const Ray &r, Hit &h, float tmin) {
  Matrix4f transformInv = transform.inverse();

  Vector3f newRayOrigin = (transform * Vector4f(r.getOrigin(), 1.0f)).xyz();
  Vector3f newRayDir = (transform * Vector4f(r.getDirection(), 0.0f)).xyz();
  newRayDir = newRayDir.normalized();
  Ray newRay(newRayOrigin, newRayDir);

  if (o->intersect(newRay, h, tmin)) {
    Vector3f normal = (transformInv * Vector4f(h.getNormal(), 0.0)).xyz();
    normal = normal.normalized();
    h.set(h.getT(), h.getMaterial(), normal);
    return true;
  }

  return false;
}
