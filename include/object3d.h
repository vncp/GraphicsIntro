#ifndef __OBJECT3D_H__
#define __OBJECT3D_H__

#include <iostream>
#include <vector>

#include "graphics_headers.h"
#include "argwrapper.h"

class Object3D : public ArgWrapper {
public:
  // Identity
  static unsigned long s_object3DIdGen;
  unsigned long m_id;
  std::string m_name;

  // Transforms

  // Object Hierarchy
  Object3D *m_parent;
  std::vector<Object3D> *m_children;

  // Methods
  Object3D(Args *args = nullptr);
  ~Object3D();

  glm::mat4 getModelMatrix();
  void render();

protected:
  glm::mat4 m_mMat;
  glm::mat4 m_tMat;

  // Mesh
  std::vector<Vertex> m_vertices;
  std::vector<unsigned int> m_indices;

  // Buffer Locations
  GLuint m_VB;
  GLuint m_IB;

  // Methods
  void setVI(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
  void initBuffers();
};

#endif /* __OBJECT3D_H__ */
