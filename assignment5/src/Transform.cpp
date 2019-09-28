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
Vector3f Ro = r.getOrigin();
        Vector3f Rd = r.getDirection();
        Matrix4f m_inv = this->transform.inverse();
        Ray r_trans = Ray((m_inv * Vector4f(Ro, 1.0)).xyz(), (m_inv * Vector4f(Rd, 0.0)).xyz());
        if (o->intersect(r_trans, h , tmin)) {
            Vector3f normal = (m_inv.transposed() * Vector4f(h.getNormal(), 0.0)).xyz().normalized();
            h.set(h.getT(), h.getMaterial(), normal);
            return true;
        }
        return false;
/*
  Matrix4f transformInv = transform.inverse();

  Vector3f newRayOrigin = (transformInv * Vector4f(r.getOrigin(), 1.0f)).xyz();
  Vector3f newRayDir = (transformInv * Vector4f(r.getDirection(), 0.0f)).xyz();
  Ray newRay(newRayOrigin, newRayDir.normalized());

  if (o->intersect(newRay, h, tmin)) {
    Vector3f normal = (transformInv.transposed() * Vector4f(h.getNormal(), 0.0)).xyz();
    normal = normal.normalized();
    h.set(h.getT(), h.getMaterial(), normal);
    return true;
  }

  return false;
*/
}
