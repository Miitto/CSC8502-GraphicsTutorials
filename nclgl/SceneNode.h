#pragma once

#include "../nclgl/Matrix4.h"
#include "../nclgl/Mesh.h"
#include "../nclgl/Vector3.h"
#include "../nclgl/Vector4.h"
#include <memory>

namespace renderer {
  namespace scene {
    class Node {
    protected:
      Node(std::shared_ptr<Node>& me,
           const std::shared_ptr<Mesh>& mesh = nullptr,
           Vector4 color = Vector4(1, 1, 1, 1));

    public:
      struct Transforms {
        Matrix4 local;
        Matrix4 world;
      };

      Node(const Node&) = delete;
      ~Node() = default;

      static std::shared_ptr<Node>&
      create(const std::shared_ptr<Mesh>& mesh = nullptr,
             const Vector4& color = Vector4(1, 1, 1, 1));

      inline void SetTransform(const Matrix4& matrix) {
        m_transforms.local = matrix;
      }
      inline const Transforms& GetTransforms() const { return m_transforms; }

      inline void SetScale(const Vector3& scale) { m_scale = scale; }
      inline void SetColor(const Vector4& color) { m_color = color; }

      inline const std::shared_ptr<Node>& GetParent() const { return m_parent; }
      inline std::shared_ptr<Node>& GetParent() { return m_parent; }
      inline const std::shared_ptr<Mesh>& GetMesh() const { return m_mesh; }
      inline const Vector3& GetScale() const { return m_scale; }
      inline const Vector4& GetColor() const { return m_color; }

      void AddChild(const std::shared_ptr<Node>& child);

      virtual void Update(float dt);
      virtual void Draw(const OGLRenderer& r);

      std::vector<std::shared_ptr<Node>>& GetChildren() { return m_children; }
      std::vector<std::shared_ptr<Node>>::iterator begin() {
        return m_children.begin();
      }
      std::vector<std::shared_ptr<Node>>::iterator end() {
        return m_children.end();
      }
      std::vector<std::shared_ptr<Node>>::const_iterator begin() const {
        return m_children.begin();
      }
      std::vector<std::shared_ptr<Node>>::const_iterator end() const {
        return m_children.end();
      }
      std::vector<std::shared_ptr<Node>>::const_iterator cbegin() const {
        return m_children.cbegin();
      }
      std::vector<std::shared_ptr<Node>>::const_iterator cend() const {
        return m_children.cend();
      }

    protected:
      std::shared_ptr<Node>& m_me;
      std::shared_ptr<Node> m_parent = nullptr;
      Transforms m_transforms = {};
      std::shared_ptr<Mesh> m_mesh = nullptr;
      Vector3 m_scale = {};
      Vector4 m_color = {};
      std::vector<std::shared_ptr<Node>> m_children = {};
    };
  } // namespace scene
} // namespace renderer
