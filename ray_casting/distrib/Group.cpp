/*************************************************************************
    > File Name: Group.cpp
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Sat Apr 13 22:11:27 2019
 ************************************************************************/

#include "Group.h"

#include<iostream>
#include<cstdlib>
using namespace std;

Group::Group() {
  objects_ = nullptr;
  num_objects_ = 0;
}

Group::Group(int num_objects) {
  objects_ = (Object3D**) malloc(num_objects * sizeof(Object3D*));
  num_objects_ = num_objects;
}

Group::~Group() {
  // delete the objects.
  delete objects_;
}

bool Group::intersect(const Ray& r, Hit& h, float t_min) {
  bool result = false;
  for (int i = 0; i < num_objects_; ++i) {
    if (objects_[i] != nullptr) {
      result |= objects_[i]->intersect(r, h, t_min);
    }
  }

  return result;
}

void Group::addObject(int index, Object3D* obj) {
  if (index < 0 || index >= num_objects_) {
    // print error when we can not add objects to the group.
    cerr << "Unable to insert this object to the group: Out of index";
  }
  objects_[index] = obj;
}

int Group::getGroupSize() {
  return num_objects_;
}

