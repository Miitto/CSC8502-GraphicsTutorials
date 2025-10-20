#pragma once

#include "../NCLGL/OGLRenderer.h"

class Renderer : public OGLRenderer {
public:
  Renderer(Window &parent);
  virtual ~Renderer(void);
  virtual void RenderScene() override;

protected:
  Mesh *m_triangleMesh;
  Shader *m_triShader;
};
