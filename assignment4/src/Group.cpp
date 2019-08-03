/* Copyright 2019 The Microsoft Edge authors */

#include "Group.h"

#include <new>

Group::Group(int num_objects) {
  numObj_ = num_objects;
  data_ = new (nothrow) Object3D*[num_objects];

  if (data_ == nullptr) {
    std::cerr << "Group: init failed";
  }
}

void Group::addObject(int index, Object3D* newObj) {
  if (index >= numObj_) {
    std::cerr << "Group: Add object failed, out of index";
  }

  data_[index] = newObj;
}

bool Group::intersect(const Ray& r, Hit& h, float tmin) {
  bool result = false;
  for (int i = 0; i < numObj_; ++i) {
    if (data_[i] != nullptr) {
      result |= data_[i]->intersect(r, h, tmin);
    }
  }

  return result;
}
