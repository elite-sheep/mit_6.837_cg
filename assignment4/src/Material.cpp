/* Copyright 2019 The Microsoft Edge authors */

#include "Material.h"

Vector3f Material::Shade(const Ray& ray,
    const Hit& hit,
    const Vector3f& dirToLight,
    const Vector3f& lightColor) {
  Vector3f diffuse;
  float angleLightNormal = Vector3f::dot(dirToLight, hit.getNormal());

  if (angleLightNormal > 0) {
    diffuse = angleLightNormal * diffuseColor_ * lightColor;
  } else {
    diffuse = Vector3f::ZERO;
  }

  return diffuse;
}
