/* Copyright 2019 Yuchen Wang */

#include "Sphere.h"

#include <cmath>

Sphere::Sphere(Vector3f center, float radius, Material* material)
  :center_(center),
  radius_(radius),
  Object3D(material) {}

/* return if the Ray is intersected with
 * this sphare and write the hit point */
bool Sphere::intersect(const Ray& r, Hit& h, float tmin) {
  // Set the center of this sphare as the Center for simplication
  Vector3f ray_origin = r.getOrigin() - center_;

  float a = Vector3f::dot(r.getDirection(), r.getDirection());
  float b = 2.0f * Vector3f::dot(ray_origin, r.getDirection());
  float c = Vector3f::dot(ray_origin, ray_origin) - radius_ * radius_;

  bool have_answer = false;
  if (b*b > 4*a*c) {
    float t1 = (-b + sqrt(b*b-4*a*c)) / (2.0f * a);
    if (t1 > tmin && t1 < h.getT()) {
      have_answer = true;
      // Use the world coordinate here
      Vector3f p = r.getOrigin() + t1 * r.getDirection();
      Vector3f normal = p - center_;
      normal.normalized();
      h.set(t1, material, normal);
    }

    float t2 = (-b - sqrt(b*b-4*a*c)) / (2.0f * a);
    if (t2 > tmin && t2 < h.getT()) {
      have_answer = true;
      // Use the world coordinate here
      Vector3f p = r.getOrigin() + t2 * r.getDirection();
      Vector3f normal = p - center_;
      normal.normalized();
      h.set(t2, material, normal);
    }
  }

  return have_answer;
}
