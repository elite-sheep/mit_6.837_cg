#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H

#include <vecmath.h>
#include <vector>
#include <GL/glut.h>

#include "particleSystem.h"

class PendulumSystem: public ParticleSystem
{
public:
	PendulumSystem(int numParticles);
	
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();
	
private:
  vector<float> m_masses;
private:
  Vector3f generateGravity(int);
  Vector3f generateSpringForce(const Vector3f&, float, float);
  Vector3f generateViscousForce(const Vector3f&, float);
};

#endif
