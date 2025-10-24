#include "Renderer.h"

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
  auto cube = std::shared_ptr<Mesh>(Mesh::LoadFromMeshFile("OffsetCubeY.msh"));

  shader = std::make_unique<Shader>("scene.vert.glsl", "scene.frag.glsl");

  if (!shader->LoadSuccess()) {
    return;
  }

  projMatrix =
      Matrix4::Perspective(1.0f, 10000.f, (float)width / (float)height, 45.f);

  camera.SetPosition({0, 30, 175});

  robot = Robot::create(cube);

  glEnable(GL_DEPTH_TEST);
  init = true;
}

void Renderer::RenderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  BindShader(nullptr);

  UpdateShaderMatrices();
  glUniform1i(glGetUniformLocation(shader->GetProgram(), "diffuseTex"), 1);

  DrawNode(*robot);
}

void Renderer::UpdateScene(float dt) {
  camera.UpdateCamera(dt);
  viewMatrix = camera.BuildViewMatrix();
  robot->Update(dt);
}

void Renderer::DrawNode(renderer::scene::Node& node) {
  if (node.GetMesh()) {
    auto model = node.GetTransforms().world * Matrix4::Scale(node.GetScale());
    glUniformMatrix4fv(
        glGetUniformLocation(shader->GetProgram(), "modelMatrix"), 1, false,
        model.values);
    glUniform4fv(glGetUniformLocation(shader->GetProgram(), "nodeColor"), 1,
                 &node.GetColor().x);
    glUniform1i(glGetUniformLocation(shader->GetProgram(), "useTexture"), 0);

    node.Draw(*this);
  }

  for (auto& child : node) {
    DrawNode(*child);
  }
}
