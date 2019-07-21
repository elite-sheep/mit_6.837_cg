#include "particleSystem.h"

#include <iostream>
#include <random>

ParticleSystem::ParticleSystem(int nParticles):m_numParticles(nParticles){
}

// generate a random number with uniform distribution
float ParticleSystem::generateRandomNumber(float l, float r) {
  float ratio = (float)rand() / RAND_MAX;
  float result = l + ratio * (r - l);

  return result;
}
