/*************************************************************************
    > File Name: src/Triangle.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: 2019年08月11日 星期日 17时14分21秒
 ************************************************************************/

#include "Triangle.h"

#include "Hit.h"

Triangle::Triangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m): Object3D(m),
  hasTex(false),
  a_(a),
  b_(b),
  c_(c) {
  }

bool Triangle::intersect(const Ray &ray, Hit& hit, float tmin) {
  Vector3f origin = ray.getOrigin();
  Vector3f direction = ray.getDirection();

  float ACramer = Matrix3f(a_.x()-b_.x(), a_.x()-c_.x(), direction.x(),
      a_.y()-b_.y(), a_.y()-c_.y(), direction.y(),
      a_.z()-b_.z(), a_.z()-c_.z(), direction.z()).determinant();
  float betaCramer = Matrix3f(a_.x()-origin.x(), a_.x()-c_.x(), direction.x(),
      a_.y()-origin.y(), a_.y()-c_.y(), direction.y(),
      a_.z()-origin.z(), a_.z()-c_.z(), direction.z()).determinant();
  float gammaCramer = Matrix3f(a_.x()-b_.x(), a_.x()-origin.x(), direction.x(),
      a_.y()-b_.y(), a_.y()-origin.y(), direction.y(),
      a_.z()-b_.z(), a_.z()-origin.z(), direction.z()).determinant();
  float tCramer = Matrix3f(a_.x()-b_.x(), a_.x()-c_.x(), a_.x()-origin.x(),
      a_.y()-b_.y(), a_.y()-c_.y(), a_.y()-origin.y(),
      a_.z()-b_.z(), a_.z()-c_.z(), a_.z()-origin.z()).determinant();

  float beta = betaCramer / ACramer;
  float gamma = gammaCramer / ACramer;
  float t = tCramer / ACramer;

  if (t >= tmin && t < hit.getT() && beta + gamma <= 1.0f && beta >= 0.0 && gamma >= 0.0) {
    float alpha = 1 - beta - gamma;
    Vector3f normal = alpha * normals[0] + beta * normals[1] + gamma * normals[2];

    if (hasTex) {
      hit.setTexCoord(alpha * texCoords[0] + beta * texCoords[1] + gamma * texCoords[2]);
      std::cout << hit.texCoord[0] << hit.texCoord[1] << std::endl;
    }
    hit.set(t, this->material, normal.normalized());

    return true;
  }

  return false;
}
