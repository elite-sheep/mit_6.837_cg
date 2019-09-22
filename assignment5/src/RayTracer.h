#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include <cassert>
#include <vector>
#include "SceneParser.h"
#include "ArgsParser.h"
#include "Ray.h"
#include "Hit.h"
#include "Group.h"

class SceneParser;


class RayTracer
{
public:
  
  RayTracer()
  {
      assert( false );
  }

  RayTracer(SceneParser*, Args);
  ~RayTracer();
  
  Vector3f traceRay( Ray& ray, float tmin, int bounces, 
                     float refr_index, Hit& hit ) const;
private:
  Group* g;
  SceneParser* sceneParser_;
  Args args_;

  int m_maxBounces;

};

#endif // RAY_TRACER_H
