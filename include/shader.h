#ifndef SHADER_H
#define SHADER_H

#include <vector>

#include "graphics_headers.h"
#include "argwrapper.h"

class Shader : public ArgWrapper
{
  public:
    Shader(Args *args);
    ~Shader();
    bool Initialize();
    void Enable();
    bool AddShader(GLenum ShaderType);
    void readShaderSource(const char *filePath, std::string &s);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

  private:
    GLuint m_shaderProg;
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */
