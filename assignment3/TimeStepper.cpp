#include "TimeStepper.hpp"

#include <iostream>

///TODO: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
  if (particleSystem == nullptr) {
    std::cerr << "ForwardEuler::takeStep: particleSystem not existed.";
    return;
  }

  vector<Vector3f> currentState = particleSystem->getState();
  vector<Vector3f> currentStateDir = particleSystem->evalF(currentState);
  vector<Vector3f> nextState;

  for (unsigned i = 0; i < currentState.size(); ++i) {
    Vector3f p = currentState[i] + stepSize * currentStateDir[i];
    nextState.push_back(p);
  }

  particleSystem->setState(nextState);
}

///TODO: implement Trapzoidal rule here
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
  if (particleSystem == nullptr) {
    std::cerr << "ForwardEuler::takeStep: particleSystem not existed.";
    return;
  }

  vector<Vector3f> currentState = particleSystem->getState();
  vector<Vector3f> currentStateDir = particleSystem->evalF(currentState);
  vector<Vector3f> currentStateDir2 = particleSystem->evalF(currentStateDir);
  vector<Vector3f> nextState;

  for (unsigned i = 0; i < currentState.size(); ++i) {
    Vector3f nextP = currentState[i] + 
      0.5f * stepSize * (currentStateDir[i] + currentStateDir[i] + stepSize * currentStateDir2[i]);
    nextState.push_back(nextP);
  }

  particleSystem->setState(nextState);
}
