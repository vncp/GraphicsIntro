#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "eventhandler.h"
#include "argwrapper.h"

class Graphics : public ArgWrapper
{
  public:
    Graphics(EventHandler *eventHandler, Args *args = nullptr);
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();

  private:
    std::string ErrorString(GLenum error);

    EventHandler *m_eventHandler;
    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object *m_cube;
};

#endif /* GRAPHICS_H */
