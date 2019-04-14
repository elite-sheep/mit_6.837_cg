/*************************************************************************
    > File Name: PerspectiveCamera.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Sun Apr 14 10:17:30 2019
 ************************************************************************/

#include "PerspectiveCamera.h"

#include<iostream>
#include<cmath>
using namespace std;

PerspectiveCamera::PerspectiveCamera(const Vector3f& center,
    const Vector3f& direction, const Vector3f& up, float angle)
  : center_(center),
  direction_(direction),
  up_(up),
  angle_(angle) {
    horizontal_ = Vector3f::cross(direction_, up_);
    horizontal_.normalized();
  }

float PerspectiveCamera::getTMin() const {
  return 0.0f;
}

// Generate the ray for the camera
// point is a coordinate in the screen-space which both width and height are ranged in [0.0, 1.0]
Ray PerspectiveCamera::generateRay(const Vector2f& point) {
  float distance_to_screen = 1.0 / (2.0 * tan(angle_ / 2.0f));
  Vector3f dir = distance_to_screen * direction_ + point[0] * horizontal_ + point[1] * up_;
  return Ray(center_, dir);
}

