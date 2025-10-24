#pragma once

#include "../nclgl/OGLRenderer.h"

class Renderer : public OGLRenderer {
public:
  Renderer(Window &parent);
  virtual ~Renderer(void);

  void RenderScene() override;

  inline void ToggleObject() { modifyObject = !modifyObject; }
  inline void ToggleDepth() { usingDepth = !usingDepth; }
  inline void ToggleAlphaBlend() { usingAlpha = !usingAlpha; }
  inline void ToggleBlendMode() { blendMode = (blendMode + 1) % 3; }
  inline void MoveObject(float by) { positions[(int)modifyObject].z += by; }

protected:
  Mesh *meshes[2];
  GLuint textures[2];
  Shader *textureShader;
  Vector3 positions[2];

  bool modifyObject = true;
  bool usingDepth = false;
  bool usingAlpha = false;
  int blendMode = 0;
};
