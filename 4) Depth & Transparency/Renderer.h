#pragma once

#include "../nclgl/OGLRenderer.h"

class Renderer : public OGLRenderer {
public:
  Renderer(Window &parent);
  virtual ~Renderer(void);
  virtual void RenderScene();

protected:
  Mesh *triMesh;
  Shader *textureShader;
  GLuint tex;
  bool filtering;
  bool repeating;
};
