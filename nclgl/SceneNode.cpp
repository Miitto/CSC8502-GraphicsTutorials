#include "SceneNode.h"

namespace renderer::scene {
  Node::Node(const std::shared_ptr<Mesh>& mesh, Vector4 color)
      : m_mesh(mesh), m_color(color), m_scale(1.0f, 1.0f, 1.0f) {}

  void Node::AddChild(const std::shared_ptr<Node>& child) {
    m_children.emplace_back(child);
    child->m_parent = this;
    child->UpdateBoundingRadius();
  }

  void Node::Update(float dt) {
    if (m_parent) {
      m_transforms.world = m_parent->m_transforms.world * m_transforms.local;
    } else {
      m_transforms.world = m_transforms.local;
    }

    for (auto& child : m_children) {
      child->Update(dt);
    }
  }

  void Node::Draw(const OGLRenderer& r, Shader& shader) {
    if (m_mesh) {
      auto model = GetTransforms().world * Matrix4::Scale(GetScale());
      glUniformMatrix4fv(
          glGetUniformLocation(shader.GetProgram(), "modelMatrix"), 1, false,
          model.values);
      glUniform4fv(glGetUniformLocation(shader.GetProgram(), "nodeColor"), 1,
                   &GetColor().x);
      glUniform1i(glGetUniformLocation(shader.GetProgram(), "useTexture"), 0);

      m_mesh->Draw();
    }

    for (auto& child : *this) {
      child->Draw(r, shader);
    }
  }

  void Node::UpdateBoundingRadius() {
    if (!m_parent)
      return;
    Vector3 relPos = m_transforms.local.GetPositionVector();
    m_parent->m_boundingRadius = std::max(m_parent->m_boundingRadius,
                                          relPos.Length() + m_boundingRadius);
    m_parent->UpdateBoundingRadius();
  }

} // namespace renderer::scene