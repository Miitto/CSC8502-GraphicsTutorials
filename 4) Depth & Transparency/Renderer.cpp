#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
  meshes[0] = Mesh::GenerateQuad();
  meshes[1] = Mesh::GenerateTriangle();

  textureShader = new Shader("tex.vert.glsl", "tex.frag.glsl");

  if (!textureShader->LoadSuccess()) {
    return;
  }

  textures[0] = SOIL_load_OGL_texture(TEXTUREDIR "brick.tga", SOIL_LOAD_AUTO,
                                      SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
  if (!textures[0]) {
    std::cout << "SOIL loading error: '" << SOIL_last_result() << "' (brick)"
              << std::endl;
  }

  textures[1] = SOIL_load_OGL_texture(TEXTUREDIR "stainedglass.tga",
                                      SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

  if (!textures[1]) {
    std::cerr << "SOIL loading error: '" << SOIL_last_result()
              << "' (stainedglass)" << std::endl;
  }

  positions[0] = Vector3(.0f, 0.0f, -5.0f);
  positions[1] = Vector3(.0f, 0.0f, -5.0f);

  projMatrix =
      Matrix4 ::Perspective(1.0f, 100.0f, (float)width / (float)height, 45.0f);

  init = true;
}

Renderer::~Renderer(void) {
  delete meshes[0];
  delete meshes[1];
  delete textureShader;
  glDeleteTextures(2, textures);
}

void Renderer::RenderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  BindShader(textureShader);
  UpdateShaderMatrices();

  glUniform1i(glGetUniformLocation(textureShader->GetProgram(), "diffuseTex"),
              0);
  glActiveTexture(GL_TEXTURE0);

  if (usingDepth) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }

  if (usingAlpha) {
    glEnable(GL_BLEND);
    switch (blendMode) {
    case 0:
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      break;
    case 1:
      glBlendFunc(GL_ONE, GL_ONE);
      break;
    case 2:
      glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
      break;
    }
  } else {
    glDisable(GL_BLEND);
  }

  for (int i = 0; i < 2; ++i) {
    glBindTexture(GL_TEXTURE_2D, textures[i]);
    modelMatrix = Matrix4::Translation(positions[i]);
    glUniformMatrix4fv(
        glGetUniformLocation(textureShader->GetProgram(), "modelMatrix"), 1,
        false, modelMatrix.values);
    meshes[i]->Draw();
  }
}