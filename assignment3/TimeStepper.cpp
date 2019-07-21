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
  vector<Vector3f> d1 = particleSystem->evalF(currentState);
  vector<Vector3f> next;
  for (unsigned i = 0; i < currentState.size(); ++i) {
    next.push_back(currentState[i] + d1[i] * stepSize);
  }
  vector<Vector3f> d2 = particleSystem->evalF(next);

  vector<Vector3f> result;
  for (unsigned i = 0; i < currentState.size(); ++i) {
    Vector3f nextP = currentState[i] + 
      0.5f * stepSize * (d1[i] + d2[i]);
    result.push_back(nextP);
  }

  particleSystem->setState(result);
}

void RK4::takeStep(ParticleSystem* particleSystem, float stepSize)
{
  if (particleSystem == nullptr) {
    std::cerr << "RK4::takeStep: particleSystem not existed.";
    return;
  }

  vector<Vector3f> currentState = particleSystem->getState();
  vector<Vector3f> k1 = particleSystem->evalF(currentState);

  vector<Vector3f> k1State;
  for (unsigned i = 0; i < currentState.size(); ++i) {
    k1State.push_back(currentState[i] + stepSize * 0.5f * k1[i]);
  }

  vector<Vector3f> k2 = particleSystem->evalF(k1State);
  vector<Vector3f> k2State;
  for (unsigned i = 0; i < currentState.size(); ++i) {
    k2State.push_back(currentState[i] + stepSize * 0.5f * k2[i]);
  }

  vector<Vector3f> k3 = particleSystem->evalF(k2State);
  vector<Vector3f> k3State;
  for (unsigned i = 0; i < currentState.size(); ++i) {
    k3State.push_back(currentState[i] + stepSize * 0.5f * k3[i]);
  }

  vector<Vector3f> k4 = particleSystem->evalF(k3State);

  vector<Vector3f> result;
  for (unsigned i = 0; i < currentState.size(); ++i) {
    result.push_back(currentState[i] + (k1[i] + 2.0f * k2[i] + 2.0f * k3[i] + k4[i]) * 0.166667 * stepSize);
  }

  particleSystem->setState(result);
}

