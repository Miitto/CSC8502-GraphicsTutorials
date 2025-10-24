#pragma once

#include "../nclgl/Matrix4.h"
#include "../nclgl/Mesh.h"
#include "../nclgl/Vector3.h"
#include "../nclgl/Vector4.h"
#include <memory>

namespace renderer {
  namespace scene {
    class Node {

    public:
      struct Transforms {
        Matrix4 local;
        Matrix4 world;
      };

      Node(const std::shared_ptr<Mesh>& mesh = nullptr,
           Vector4 color = Vector4(1, 1, 1, 1));
      ~Node() = default;

      inline void SetTransform(const Matrix4& matrix) {
        m_transforms.local = matrix;
      }
      inline const Transforms& GetTransforms() const { return m_transforms; }

      inline void SetScale(const Vector3& scale) { m_scale = scale; }
      inline void SetColor(const Vector4& color) { m_color = color; }

      void SetParent(Node* parent) { m_parent = parent; }
      inline bool HasParent() const { return m_parent != nullptr; }
      inline const Node& GetParent() const { return *m_parent; }
      inline Node& GetParent() { return *m_parent; }
      inline const std::shared_ptr<Mesh>& GetMesh() const { return m_mesh; }
      inline const Vector3& GetScale() const { return m_scale; }
      inline const Vector4& GetColor() const { return m_color; }

      void AddChild(const std::shared_ptr<Node>& child);
      void UpdateBoundingRadius();

      virtual void Update(float dt);
      virtual void Draw(const OGLRenderer& r, Shader& shader);

      inline float GetBoundingRadius() const { return m_boundingRadius; }
      inline void SetBoundingRadius(float radius) { m_boundingRadius = radius; }
      inline float GetCameraDistance() const { return m_cameraDistance; }
      inline void SetCameraDistance(float distance) {
        m_cameraDistance = distance;
      }

      inline void SetTexture(GLuint tex) { m_texture = tex; }
      inline GLuint GetTexture() const { return m_texture; }

      static inline bool CompareByCameraDistance(const Node& a, const Node& b) {
        return a.GetCameraDistance() < b.GetCameraDistance();
      }

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
      Node* m_parent = nullptr;
      Transforms m_transforms = {};
      std::shared_ptr<Mesh> m_mesh = nullptr;
      Vector3 m_scale = {};
      Vector4 m_color = {};
      std::vector<std::shared_ptr<Node>> m_children = {};

      float m_cameraDistance = 0.0f;
      float m_boundingRadius = 1.0f;
      GLuint m_texture = 0;
    };
  } // namespace scene
} // namespace renderer
