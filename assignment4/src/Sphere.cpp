/* Copyright 2019 The Microsoft Edge authors */

#include "Sphere.h"

Sphere::Sphere(Vector3f center, float radius, Material* material)
  :Object3D(material),
   radius_(radius),
   center_(center) {
   }

bool Sphere::intersect(const Ray& r, Hit& h, float tmin) {
  Vector3f ray_origin = r.getOrigin() - center_;

  float a = Vector3f::dot(r.getDirection(), r.getDirection());
  float b = 2.0f * Vector3f::dot(ray_origin, r.getDirection());
  float c = Vector3f::dot(ray_origin, ray_origin) - radius_ * radius_;
  
  bool have_answer = false;
  if (b*b >= 4*a*c) {
    float t1 = (-b + sqrt(b*b-4*a*c)) / (2.0f * a);
    if (t1 > tmin && t1 < h.getT()) {
      Vector3f p = r.getOrigin() + t1 * r.getDirection();
      Vector3f normal = p - center_;
      normal.normalized();
      h.set(t1, material, normal);
      have_answer = true;
    }

    float t2 = (-b - sqrt(b*b-4*a*c)) / (2.0f * a);
    if (t2 > tmin && t2 < h.getT()) {
      Vector3f p = r.getOrigin() + t2 * r.getDirection();
      Vector3f normal = p - center_;
      normal.normalized();
      h.set(t2, material, normal);
      have_answer = true;
    }
  }
}
