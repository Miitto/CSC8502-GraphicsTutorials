#pragma once

#include "../nclgl/Camera.h"
#include "../nclgl/OGLRenderer.h"
#include "Robot.h"

class Renderer : public OGLRenderer {
public:
  Renderer(Window& parent);
  virtual ~Renderer(void) = default;
  virtual void RenderScene();
  virtual void UpdateScene(float dt);

  void DrawNode(renderer::scene::Node& node);

protected:
  std::shared_ptr<Robot> robot;
  std::unique_ptr<Shader> shader;
  renderer::Camera camera = {};
};
