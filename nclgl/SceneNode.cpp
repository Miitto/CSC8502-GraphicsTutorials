#include "SceneNode.h"

namespace renderer::scene {
  Node::Node(std::shared_ptr<Node>& me, const std::shared_ptr<Mesh>& mesh,
             Vector4 color)
      : m_me(me), m_mesh(mesh), m_color(color), m_scale(1.0f, 1.0f, 1.0f) {}

  std::shared_ptr<Node>& Node::create(const std::shared_ptr<Mesh>& mesh,
                                      const Vector4& color) {
    std::shared_ptr<Node> me = nullptr;
    auto t = std::shared_ptr<Node>(new Node(me, mesh, color));
    t.swap(me);
    return me;
  }

  void Node::AddChild(const std::shared_ptr<Node>& child) {
    m_children.emplace_back(child);
    child->m_parent = m_me;
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