#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"

#include <iostream>
#include <vector>

using  namespace std;

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
class Group:public Object3D
{
public:

  Group();
  Group( int num_objects );

  ~Group();
  
  bool intersect( const Ray& r , Hit& h , float tmin ) override;

  void addObject( int index , Object3D* obj );

  int getGroupSize();

 private:
  Object3D** objects_;
  int num_objects_;

};

#endif
