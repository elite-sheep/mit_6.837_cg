/*************************************************************************
    > File Name: PerspectiveCamera.h
    > Author: Yuchen Wang
    > Mail: wyc8094@gmail.com 
    > Created Time: Sun Apr 14 10:11:47 2019
 ************************************************************************/

#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "Camera.h"

#include<iostream>
using namespace std;

///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle){

	}

	virtual Ray generateRay( const Vector2f& point){
		
	}

	virtual float getTMin() const { 
		return 0.0f;
	}

private:
  float angle_;

};

#endif

