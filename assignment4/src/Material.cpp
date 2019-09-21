/* Copyright 2019 The Microsoft Edge authors */

#include <algorithm>
#include <cmath>

#include "Material.h"

Vector3f Material::Shade(const Ray& ray,
    const Hit& hit,
    const Vector3f& dirToLight,
    const Vector3f& lightColor) {
  Vector3f shadeColor = Vector3f::ZERO;
  Vector3f normal = hit.getNormal().normalized();


  Vector3f textureColor = diffuseColor_;
  if (hit.hasTex && t_.valid()) {
    textureColor = t_(hit.texCoord[0], hit.texCoord[1]);
  }

  float lightColorShadingIntensity = Vector3f::dot(dirToLight, normal);
  if (lightColorShadingIntensity > 0) {
    shadeColor += lightColorShadingIntensity * textureColor * lightColor;
  }

  Vector3f reflectedDir = ray.getDirection() -
    2 * (Vector3f::dot(normal, ray.getDirection())) * normal;
  float specularShadingIntensity = Vector3f::dot(dirToLight, reflectedDir);
  if (specularShadingIntensity > 0 && lightColorShadingIntensity >= 0) {
    shadeColor = shadeColor +  lightColor * diffuseColor_ * pow(specularShadingIntensity, shininess_);
  }
  return shadeColor;
}
