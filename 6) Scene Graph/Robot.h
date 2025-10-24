#pragma once

#include "../nclgl/SceneNode.h"

class Robot : public renderer::scene::Node {

public:
  Robot() = delete;
  Robot(std::shared_ptr<Mesh>& cube);
  virtual ~Robot() = default;

  void Update(float dt) override;

protected:
  renderer::scene::Node* head;
  renderer::scene::Node* leftArm;
  renderer::scene::Node* rightArm;
};
