/* Copyright 2019 The Microsoft Edge authors */

#include <algorithm>
#include <cmath>

#include "Material.h"

Vector3f Material::Shade(const Ray& ray,
    const Hit& hit,
    const Vector3f& dirToLight,
    const Vector3f& lightColor) {
  Vector3f shadeColor = Vector3f::ZERO;

  Vector3f textureColor = diffuseColor_;
  if (hit.hasTex && t_.valid()) {
    std::cout << hit.texCoord[0] << hit.texCoord[1] << std::endl;
    textureColor = t_(hit.texCoord[0], hit.texCoord[1]);
  }

  float lightColorShadingIntensity = Vector3f::dot(dirToLight, hit.getNormal().normalized());
  if (lightColorShadingIntensity > 0) {
    shadeColor += lightColorShadingIntensity * textureColor * lightColor;
  }

  Vector3f reflectedDir = ray.getDirection() - 
    2 * (Vector3f::dot(hit.getNormal(), ray.getDirection())) * hit.getNormal();
  float specularShadingIntensity = Vector3f::dot(dirToLight, reflectedDir);
  if (lightColorShadingIntensity > 0) {
    shadeColor = shadeColor + (pow(specularShadingIntensity, shininess_)) * specularColor_ * lightColor;
  }
  return shadeColor;
}
