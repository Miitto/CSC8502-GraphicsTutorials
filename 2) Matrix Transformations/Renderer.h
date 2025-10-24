#pragma once

#include "../nclgl/Camera.h"
#include "../nclgl/OGLRenderer.h"

class Renderer : public OGLRenderer {
public:
  Renderer(Window& parent);
  virtual ~Renderer(void);
  virtual void RenderScene();
  virtual void UpdateScene(float dt);

  void SwitchToOrthographic();
  void SwitchToPerspective();

  inline void setScale(float s) { scale = s; }
  inline void setRotation(float r) { rotation = r; };
  inline void setPosition(const Vector3& t) { position = t; }

protected:
  Mesh* triangleMesh;
  Shader* mpShader;
  float scale;
  float rotation;
  Vector3 position;

  renderer::PerspectiveCamera cam;
};