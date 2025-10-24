#include "Camera.h"

#include "../nclgl/Window.h"

namespace {
const Vector3 FORWARD = Vector3(0, 0, -1);
const Vector3 UP = Vector3(0, 1, 0);
const Vector3 RIGHT = Vector3(1, 0, 0);

const float MOVE_SPEED = 30.0f;
const float FAST_MOVE_SPEED = 100.f;
} // namespace

void Camera::UpdateCamera(float dt) {
  rotation.pitch -= (Window::GetMouse()->GetRelativePosition().y);
  rotation.yaw -= (Window::GetMouse()->GetRelativePosition().x);

  if (Window::GetKeyboard()->KeyDown(KEYBOARD_UP))
    rotation.pitch += 100.0f * dt;
  if (Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN))
    rotation.pitch -= 100.0f * dt;
  if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT))
    rotation.yaw += 100.0f * dt;
  if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT))
    rotation.yaw -= 100.0f * dt;

  rotation.pitch = std::fmax(std::fmin(rotation.pitch, 89.0f), -89.0f);
  if (rotation.yaw < 0.0f)
    rotation.yaw += 360.0f;
  else if (rotation.yaw > 360.0f)
    rotation.yaw -= 360.0f;

  auto rot = Matrix4::Rotation(rotation.yaw, UP);
  auto forward = rot * FORWARD;
  auto right = rot * RIGHT;

  auto speed = MOVE_SPEED;

  auto check = [&](KeyboardKeys key, const Vector3 &dir) {
    if (Window::GetKeyboard()->KeyDown(key)) {
      position += dir * dt * speed;
    }
  };

  if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT))
    speed = FAST_MOVE_SPEED;

  check(KEYBOARD_W, forward);
  check(KEYBOARD_S, forward * -1.0f);
  check(KEYBOARD_A, right * -1.0f);
  check(KEYBOARD_D, right);

  check(KEYBOARD_Q, UP);
  check(KEYBOARD_E, UP * -1.0f);

  if (Window::GetKeyboard()->KeyDown(KEYBOARD_R)) {
    rotation = {0.0f, 0.0f};
  }
}

Matrix4 Camera::BuildViewMatrix() const {
  return Matrix4::Rotation(-rotation.pitch, RIGHT) *
         Matrix4::Rotation(-rotation.yaw, UP) * Matrix4::Translation(-position);
}
