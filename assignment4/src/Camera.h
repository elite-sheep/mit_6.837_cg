#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera
{
public:
  Camera(const Vector3f& center, const Vector3f& direction, const Vector3f& up):
    center_(center),
    direction_(direction.normalized()),
    up_(up) {}

	//generate rays for each screen-space coordinate
	virtual Ray generateRay( const Vector2f& point ) = 0 ; 
	
	virtual float getTMin() const = 0 ; 
	virtual ~Camera(){}
protected:
	Vector3f center_; 
	Vector3f direction_;
	Vector3f up_;
	Vector3f horizontal_;

};

///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle):
    Camera(center, direction, up),
    angle_(angle) {
      horizontal_ = Vector3f::cross(direction_, up_).normalized();
    }

	virtual Ray generateRay( const Vector2f& point){
    float distanceToScreen = 1.0 / tan(angle_ / 2.0f);
    Vector3f dir = distanceToScreen * direction_ + point[0] * horizontal_ + point[1] * up_;
    return Ray(center_, dir);
	}

	virtual float getTMin() const { 
		return 0.0f;
	}

private:
  float angle_;

};

#endif //CAMERA_H
