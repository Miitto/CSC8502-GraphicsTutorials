#pragma once

#include "../nclgl/SceneNode.h"

class Robot : public renderer::scene::Node {
protected:
  Robot(std::shared_ptr<Node> me, std::shared_ptr<renderer::scene::Node>& head,
        std::shared_ptr<renderer::scene::Node>& leftArm,
        std::shared_ptr<renderer::scene::Node>& rightArm)
      : renderer::scene::Node(me), head(head), leftArm(leftArm),
        rightArm(rightArm) {}

public:
  Robot(const Robot&) = delete;
  virtual ~Robot() = default;

  void Update(float dt) override;

  static std::shared_ptr<Robot> create(std::shared_ptr<Mesh>& cube);

protected:
  std::shared_ptr<renderer::scene::Node>& head;
  std::shared_ptr<renderer::scene::Node>& leftArm;
  std::shared_ptr<renderer::scene::Node>& rightArm;
};
