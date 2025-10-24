#pragma once

#include "Camera.h"
#include "SceneNode.h"

namespace renderer {
  namespace scene {
    class Graph {
    public:
      Graph() = default;
      ~Graph() = default;

      // Non-copyable
      Graph(const Graph&) = delete;
      Graph& operator=(const Graph&) = delete;

      // Update parent pointers after move. Lets Graph & root sit on stack.
      // Maybe a minor performance benefit?
      inline Graph(Graph&& o) noexcept {
        root = std::move(o.root);
        for (auto& child : root.GetChildren()) {
          child->SetParent(&root);
        }
      }
      inline Graph& operator=(Graph&& o) noexcept {
        if (this != &o) {
          root = std::move(o.root);
          for (auto& child : root.GetChildren()) {
            child->SetParent(&root);
          }
        }
        return *this;
      }

      inline void AddChild(const std::shared_ptr<Node>& child) {
        root.AddChild(child);
      }

      struct NodeLists {
        std::vector<Node*> opaque;
        std::vector<Node*> transparent;

        inline void Draw(const OGLRenderer& renderer, Shader& shader) const {
          for (const auto node : opaque) {
            node->Draw(renderer, shader);
          }
          for (const auto node : transparent) {
            node->Draw(renderer, shader);
          }
        }
      };

      NodeLists BuildNodeLists(const renderer::Camera& camera);

      inline void Update(float dt) { root.Update(dt); }

    protected:
      Node root;
    };
  } // namespace scene
} // namespace renderer
