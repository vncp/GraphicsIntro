#ifndef CAMERA_H
#define CAMERA_H

#include "object3d.h"
#include "graphics_headers.h"
#include "argwrapper.h"

class Camera : public Object3D
{
  public:
    Camera(Args *args = nullptr);
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();

  private:
    glm::mat4 projection;
    glm::mat4 view;
};

#endif /* CAMERA_H */
