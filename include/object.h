#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include "argwrapper.h"
#include "object3d.h"
#include "eventhandler.h"

class Object : public Object3D, public Listener
{
  public:
    Object(Args *args = nullptr);
    ~Object();
    void Update(unsigned int dt);
    void toggleSpin();
    void toggleSpinDirection();
    void toggleOrbit();
    void toggleOrbitDirection();
  private:
    void handleEvent(int key) override;
    void handleEvent(int key, float *val) override;
    float angleOrbit;
    float angleSpin;
    glm::mat4 orbitMat;
    glm::mat4 spinMat;
    glm::mat4 transMat;
    bool isSpinning;
    bool isSpinClockwise;
    bool isOrbitting;
    bool isOrbittingClockwise;
    float spinMultiplier;
    float orbitMultiplier;
};

#endif /* OBJECT_H */
