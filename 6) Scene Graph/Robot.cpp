#include "Robot.h"

std::shared_ptr<Robot> Robot::create(std::shared_ptr<Mesh>& cube) {
  std::shared_ptr<Robot> me = nullptr;

  auto body =
      renderer::scene::Node::create(cube, Vector4(0.8f, 0.2f, 0.2f, 1.0f));
  body->SetScale({10, 15, 5});
  body->SetTransform(Matrix4::Translation(Vector3(0, 35, 0)));

  auto head =
      renderer::scene::Node::create(cube, Vector4(0.2f, 0.8f, 0.2f, 1.0f));
  head->SetScale({5, 5, 5});
  head->SetTransform(Matrix4::Translation({0, 30, 0}));

  auto leftArm =
      renderer::scene::Node::create(cube, Vector4(0.2f, 0.2f, 0.8f, 1.0f));
  leftArm->SetScale({3, -18, 3});
  leftArm->SetTransform(Matrix4::Translation({-12, 30, -1}));

  auto rightArm =
      renderer::scene::Node::create(cube, Vector4(0.2f, 0.2f, 0.8f, 1.0f));
  rightArm->SetScale({3, -18, 3});
  rightArm->SetTransform(Matrix4::Translation({12, 30, -1}));

  auto leftLeg =
      renderer::scene::Node::create(cube, Vector4(0.8f, 0.8f, 0.2f, 1.0f));
  leftLeg->SetScale({3, -17.5, 3});
  leftLeg->SetTransform(Matrix4::Translation({-8, 0, 0}));

  auto rightLeg =
      renderer::scene::Node::create(cube, Vector4(0.8f, 0.8f, 0.2f, 1.0f));
  rightLeg->SetScale({3, -17.5, 3});
  rightLeg->SetTransform(Matrix4::Translation({8, 0, 0}));

  auto t = std::shared_ptr<Robot>(new Robot(me, head, leftArm, rightArm));
  t.swap(me);

  me->AddChild(body);
  me->AddChild(head);
  me->AddChild(leftArm);
  me->AddChild(rightArm);
  me->AddChild(leftLeg);
  me->AddChild(rightLeg);

  return me;
}

void Robot::Update(float dt) {
  m_transforms.local =
      m_transforms.local * Matrix4::Rotation(30.f * dt, {0, 1, 0});

  head->SetTransform(head->GetTransforms().local *
                     Matrix4::Rotation(-30.f * dt, {0, 1, 0}));

  leftArm->SetTransform(leftArm->GetTransforms().local *
                        Matrix4::Rotation(-30.f * dt, {1, 0, 0}));
  rightArm->SetTransform(rightArm->GetTransforms().local *
                         Matrix4::Rotation(30.f * dt, {1, 0, 0}));

  renderer::scene::Node::Update(dt);
}
