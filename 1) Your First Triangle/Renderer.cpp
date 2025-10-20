#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
  m_triangleMesh = Mesh::GenerateTriangle();
  m_triShader = new Shader("basic.vert.glsl", "srgb_color.frag.glsl");

  if (!m_triShader->LoadSuccess()) {
    return;
  }

  init = true;
}

Renderer::~Renderer(void) {
  delete m_triangleMesh;
  delete m_triShader;
}

void Renderer::RenderScene() {
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  BindShader(m_triShader);
  m_triangleMesh->Draw();
}