#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera
{
public:
  //generate rays for each screen-space coordinate
  virtual Ray generateRay( const Vector2f& point ) = 0 ; 
  virtual float getTMin() const = 0 ; 
  virtual ~Camera(){}
};


#endif //CAMERA_H
