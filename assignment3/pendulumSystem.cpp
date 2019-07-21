
#include "pendulumSystem.h"

#include <iostream>
#include <vector>

const float minDis = -2.5;
const float maxDis = 2.5;
const float minMass = 0.05;
const float maxMass = 0.2;
const float G = 9.8;
const float K = 4.0;
const float r = 2.0;
const float ViscousConstant = 0.05;

PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
  m_numParticles = numParticles;
  
  // fill in code for initializing the state based on the number of particles
  vector<Vector3f> initSystem;
  for (int i = 0; i < m_numParticles; i++) {
    // for this system, we care about the position and the velocity
    initSystem.push_back(Vector3f(generateRandomNumber(minDis, maxDis), generateRandomNumber(minDis, maxDis), 0.0));
    initSystem.push_back(Vector3f(0.0f, 0.0f, 0.0f));
    m_masses.push_back(generateRandomNumber(minMass, maxMass));

    std::cout << m_masses[i] << std::endl;
  }
  setState(initSystem);
}

Vector3f PendulumSystem::generateGravity(int index) {
  return Vector3f(0.0f, -1.0f * G * m_masses[index], 0.0);
}

Vector3f PendulumSystem::generateSpringForce(const Vector3f& pos, float r, float k) {
  return -1.0f * k * (pos.abs() - r) * pos.normalized();
}

Vector3f PendulumSystem::generateViscousForce(const Vector3f& velocity, float viscousConstant) {
  return -1.0f * viscousConstant * velocity;
}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
  if (state.size() != m_numParticles * 2) {
    std::cerr << "PendulumSystem::evalF: Please check the state you give.";
    return state;
  }
	vector<Vector3f> f;

  for (int i = 0; i < m_numParticles; ++i) {
    f.push_back(state[i * 2 + 1]);

    Vector3f gravity = generateGravity(i);
    Vector3f springForce = generateSpringForce(state[i * 2], r, K);
    Vector3f viscousForce = generateViscousForce(state[i * 2 + 1], ViscousConstant);
    //std::cout << dragForce.x() << " " << dragForce.y() << std::endl;
    f.push_back(gravity + springForce + viscousForce);
  }

	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		Vector3f pos = m_vVecState[2 * i];//  position of particle i. YOUR CODE HERE
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
    //std::cout << pos[0] << " " << pos[1] << std::endl;
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
}
