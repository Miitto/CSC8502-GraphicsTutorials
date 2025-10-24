#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent), cam(Camera()) {
  triangleMesh = Mesh::GenerateTriangle();

  mpShader = new Shader("mp.vert.glsl", "srgb_color.frag.glsl");

  if (!mpShader->LoadSuccess()) {
    return;
  }

  init = true;

  SwitchToOrthographic();
}

Renderer::~Renderer(void) {
  delete triangleMesh;
  delete mpShader;
}

void Renderer::SwitchToOrthographic() {
  std::clog << "Switching to Orthographic Projection\n";
  projMatrix = Matrix4::Orthographic(-1.0f, 10000.0f, width / 2.f, -width / 2.f,
                                     height / 2.f, -height / 2.f);
}

void Renderer::SwitchToPerspective() {
  std::clog << "Switching to Perspective Projection\n";
  projMatrix =
      Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);
}

void Renderer::UpdateScene(float dt) {
  cam.UpdateCamera(dt);
  viewMatrix = cam.BuildViewMatrix();
}

void Renderer::RenderScene() {
  glClear(GL_COLOR_BUFFER_BIT);
  BindShader(mpShader);

  UpdateShaderMatrices();
  for (int i = 0; i < 3; ++i) {

    Vector3 tPos = position;

    tPos.z += (i * 500.f);
    tPos.x -= (i * 100.f);
    modelMatrix = Matrix4::Translation(tPos) *
                  Matrix4::Rotation(rotation, Vector3(0, 1, 0)) *
                  Matrix4::Scale(Vector3(scale, scale, scale));
    glUniformMatrix4fv(glGetUniformLocation(mpShader->GetProgram(), "model"), 1,
                       false, modelMatrix.values);

    triangleMesh->Draw();
  }
}
