#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere: public Object3D
{
public:
	Sphere(){ 
		//unit ball at the center
	}

  Sphere( Vector3f center , float radius , Material* material );

  ~Sphere(){}
  
  bool intersect( const Ray& r , Hit& h , float tmin) override;

protected:

private:
  Vector3f center_;
  float radius_;
};


#endif
