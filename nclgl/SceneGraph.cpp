#include "SceneGraph.h"
#include <algorithm>
#include <functional>

namespace renderer::scene {
  Graph::NodeLists Graph::BuildNodeLists(const renderer::Camera& camera) {
    NodeLists lists;

    auto& frustum = camera.GetFrustum();

    auto addNodeToList = [&](Node& node) {
      Vector3 nodePos = node.GetTransforms().world.GetPositionVector();
      auto relCamPos = nodePos - camera.GetPosition();
      float dist = Vector3::Dot(relCamPos, relCamPos); // Squared distance
      node.SetCameraDistance(dist);
      if (node.GetColor().w < 1.0f) {
        lists.transparent.push_back(&node);
      } else {
        lists.opaque.push_back(&node);
      }
    };

    std::function<void(Node&)> addNodeAndChildren = [&](Node& node) {
      if (frustum.NodeInFrustum(node)) {
        if (node.GetMesh())
          addNodeToList(node);

        for (const auto& child : node) {
          addNodeAndChildren(*child);
        }
      }
    };

    addNodeAndChildren(root);

    auto comp = [](const Node* a, const Node* b) {
      return Node::CompareByCameraDistance(*a, *b);
    };

    std::sort(lists.opaque.begin(), lists.opaque.end(), comp);
    std::sort(lists.transparent.rbegin(), lists.transparent.rend(), comp);

    unsigned int i = 0;
    for (auto& node : lists.transparent) {
      ++i;
    }
    for (auto& node : lists.opaque) {
      ++i;
    }

    std::clog << "Total nodes in lists: " << i << std::endl;

    return lists;
  }
} // namespace renderer::scene