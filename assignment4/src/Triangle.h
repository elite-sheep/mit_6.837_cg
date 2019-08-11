#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle: public Object3D
{
public:
  Triangle();
  
  ///@param a b c are three vertex positions of the triangle
  Triangle( const Vector3f&, const Vector3f&, const Vector3f&, Material*);

  bool intersect( const Ray& ray,  Hit& hit , float tmin) override;

public:
  Vector2f texCoords[3];
  Vector3f normals[3];
  bool hasTex;

protected:

private:
  Vector3f a_;
  Vector3f b_;
  Vector3f c_;
};

#endif //TRIANGLE_H
