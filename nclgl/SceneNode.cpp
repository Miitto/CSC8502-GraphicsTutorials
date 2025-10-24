#include "SceneNode.h"

namespace renderer::scene {
  Node::Node(const std::shared_ptr<Mesh>& mesh, Vector4 color)
      : m_mesh(mesh), m_color(color), m_scale(1.0f, 1.0f, 1.0f) {}

  void Node::AddChild(const std::shared_ptr<Node>& child) {
    m_children.emplace_back(child);
    child->m_parent = this;
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

  void Node::Draw(const OGLRenderer& r) {
    if (m_mesh)
      m_mesh->Draw();
  }

} // namespace renderer::scene