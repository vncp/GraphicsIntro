#include "object3d.h"

unsigned long Object3D::s_object3DIdGen = 0;

Object3D::Object3D(Args *args)
  : ArgWrapper(args),
  m_id(s_object3DIdGen),
  m_name(""),
  m_mMat(glm::mat4(1.0f)),
  m_parent(nullptr),
  m_children(nullptr)
{
}

Object3D::~Object3D()
{
  m_vertices.clear();
  m_indices.clear();
}

void Object3D::setVI(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
  m_vertices = vertices;
  m_indices = indices;
};

void Object3D::initBuffers() {
  glGenBuffers(1, &m_VB);
  glBindBuffer(GL_ARRAY_BUFFER, m_VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &m_IB);
  glBindBuffer(GL_ARRAY_BUFFER, m_IB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
}

glm::mat4 Object3D::getModelMatrix() {
  return m_mMat;
}

void Object3D::render() {
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, m_VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);

  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}




