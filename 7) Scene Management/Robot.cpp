#include "Robot.h"
#include <nclgl/Camera.cpp>

using renderer::scene::Node;

Robot::Robot(std::shared_ptr<Mesh>& cube) {
  auto body = std::make_shared<Node>(cube, Vector4(0.8f, 0.2f, 0.2f, 1.0f));
  body->SetScale({10, 15, 5});
  body->SetTransform(Matrix4::Translation(Vector3(0, 35, 0)));
  body->SetBoundingRadius(15.0f);

  auto head = std::make_shared<Node>(cube, Vector4(0.2f, 0.8f, 0.2f, 1.0f));
  head->SetScale({5, 5, 5});
  head->SetTransform(Matrix4::Translation({0, 30, 0}));
  head->SetBoundingRadius(5.0f);

  auto leftArm = std::make_shared<Node>(cube, Vector4(0.2f, 0.2f, 0.8f, 1.0f));
  leftArm->SetScale({3, -18, 3});
  leftArm->SetTransform(Matrix4::Translation({-12, 30, -1}));
  leftArm->SetBoundingRadius(18.0f);

  auto rightArm = std::make_shared<Node>(cube, Vector4(0.2f, 0.2f, 0.8f, 1.0f));
  rightArm->SetScale({3, -18, 3});
  rightArm->SetTransform(Matrix4::Translation({12, 30, -1}));
  rightArm->SetBoundingRadius(18.0f);

  auto leftLeg = std::make_shared<Node>(cube, Vector4(0.8f, 0.8f, 0.2f, 1.0f));
  leftLeg->SetScale({3, -17.5, 3});
  leftLeg->SetTransform(Matrix4::Translation({-8, 0, 0}));
  leftLeg->SetBoundingRadius(17.5f);

  auto rightLeg = std::make_shared<Node>(cube, Vector4(0.8f, 0.8f, 0.2f, 1.0f));
  rightLeg->SetScale({3, -17.5, 3});
  rightLeg->SetTransform(Matrix4::Translation({8, 0, 0}));
  rightLeg->SetBoundingRadius(17.5f);

  AddChild(body);
  body->AddChild(head);
  body->AddChild(leftArm);
  body->AddChild(rightArm);
  body->AddChild(leftLeg);
  body->AddChild(rightLeg);

  this->head = head.get();
  this->leftArm = leftArm.get();
  this->rightArm = rightArm.get();
}

void Robot::Update(float dt) {
  m_transforms.local =
      m_transforms.local * Matrix4::Rotation(30.f * dt, renderer::UP);

  head->SetTransform(head->GetTransforms().local *
                     Matrix4::Rotation(-30.f * dt, renderer::UP));

  leftArm->SetTransform(leftArm->GetTransforms().local *
                        Matrix4::Rotation(-30.f * dt, renderer::RIGHT));
  rightArm->SetTransform(rightArm->GetTransforms().local *
                         Matrix4::Rotation(30.f * dt, renderer::RIGHT));

  Node::Update(dt);
}
