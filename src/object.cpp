#include "object.h"

Object::Object(Args *args)
  : Object3D(args),
  angleOrbit(0.0f),
  angleSpin(0.0f),
  isSpinning(true),
  isSpinClockwise(true),
  isOrbitting(true),
  isOrbittingClockwise(true),
  spinMultiplier(1.0f),
  orbitMultiplier(1.0f)
{
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.angleOrbit
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  std::vector<Vertex> vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}}, {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  std::vector<unsigned int> indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < indices.size(); i++)
  {
    indices[i] = indices[i] - 1;
  }
  setVI(vertices, indices);
  initBuffers();

  transMat = glm::translate(glm::mat4(1.0f), glm::vec3(7.0f, 0.0f, 0.0f));
}

Object::~Object()
{
}

void Object::Update(unsigned int dt)
{
  if (isOrbitting) {
    // Calculate Orbit Angle
    if (isOrbittingClockwise)
      angleOrbit += orbitMultiplier * dt * M_PI/1000;
    else
      angleOrbit -= orbitMultiplier * dt * M_PI/1000;
    // Set Transform Matrix
    orbitMat = glm::rotate(glm::mat4(1.0f), (angleOrbit), glm::vec3(0.0f, 1.0f, 0.0f));
  }

  if (isSpinning) {
    // Caculate Angle based on spin
    if (isSpinClockwise)
      angleSpin += spinMultiplier * dt * M_PI/500;
    else
      angleSpin -= spinMultiplier * dt * M_PI/500;
    // Set Rotation Matrix
    spinMat = glm::rotate(glm::mat4(1.0f), (angleSpin), glm::vec3(0.0f, 1.0f, 0.0f));
  }

  // Calculate Transform Stack
  // Note: Applying the inverse of the orbit transform in order to let spinMatrix
  // determine entirely the spin of the model. This means spin will change at same
  // speed regardless of whether the object is rotating or not.
  m_mMat = orbitMat * transMat * spinMat / orbitMat;
}

void Object::toggleSpin() {
  isSpinning = !isSpinning;
}

void Object::toggleSpinDirection() {
  isSpinClockwise = !isSpinClockwise;
}

void Object::toggleOrbit() {
  isOrbitting = !isOrbitting;
}

void Object::toggleOrbitDirection() {
  isOrbittingClockwise = !isOrbittingClockwise;
}

void Object::handleEvent(int key) {
  switch (key) {
    case GLFW_KEY_Z:
      toggleSpin(); break;
    case GLFW_KEY_X:
      toggleOrbit();
      break;
    case GLFW_KEY_A:
      toggleSpinDirection();
      break;
    case GLFW_KEY_S:
      toggleOrbitDirection();
      break;
    case GLFW_MOUSE_BUTTON_LEFT:
      toggleSpinDirection();
      break;
  }
}

void Object::handleEvent(int key, float *val) {
  switch(key) {
    // Case spin speed
    case -1:
      spinMultiplier = *val;
      break;
    // Case orbit speed
    case -2:
      orbitMultiplier = *val;
      break;
  }
}
