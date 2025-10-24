#pragma once

#include "../nclgl/OGLRenderer.h"

class Renderer : public OGLRenderer {
public:
  Renderer(Window &parent);
  virtual ~Renderer(void);
  virtual void RenderScene();

  inline void ToggleRepeating() {
    repeating = !repeating;
    SetTextureRepeating(tex, repeating);
  }
  inline void ToggleFiltering() {
    filtering = !filtering;
    SetTextureFiltering(tex, filtering);
  }

  void UpdateTextureMatrix(float rotate);

protected:
  Mesh *triMesh;
  Shader *textureShader;

  GLuint tex;
  bool filtering;
  bool repeating;
};
