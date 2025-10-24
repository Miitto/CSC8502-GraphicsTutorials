#include "Renderer.h"
#include <SOIL/SOIL.h>

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
  triMesh = Mesh::GenerateTriangle();
  textureShader = new Shader("tex.vert.glsl", "tex.frag.glsl");

  if (!textureShader->LoadSuccess()) {
    return;
  }

  tex = SOIL_load_OGL_texture(TEXTUREDIR "brick.tga", SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
  if (!tex) {
    std::cout << "SOIL loading error: " << SOIL_last_result() << std::endl;
  }

  init = true;

  filtering = false;
  repeating = false;
}

Renderer::~Renderer(void) {
  delete triMesh;
  delete textureShader;
  glDeleteTextures(1, &tex);
}

void Renderer::RenderScene() {
  glClear(GL_COLOR_BUFFER_BIT);
  BindShader(textureShader);
  UpdateShaderMatrices();
  glUniform1i(glGetUniformLocation(textureShader->GetProgram(), "diffuseTex"),
              0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex);

  triMesh->Draw();
}

void Renderer::UpdateTextureMatrix(float rotate) {
  auto push = Matrix4::Translation(Vector3(-0.5f, -0.5f, 0.0f));
  auto pop = Matrix4::Translation(Vector3(0.5f, 0.5f, 0.0f));
  auto rot = Matrix4::Rotation(rotate, Vector3(0.0f, 0.0f, 1.0f));
  textureMatrix = pop * rot * push;
}
