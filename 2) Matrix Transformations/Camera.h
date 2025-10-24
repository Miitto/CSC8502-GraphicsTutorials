#pragma once
#include <nclgl/Matrix4.h>
#include <nclgl/Vector3.h>

class Camera {
public:
  struct Rotation {
    float pitch;
    float yaw;
  };

  inline Camera() : rotation({0.0, 0.0}), position({}) {}

  inline Camera(Rotation rotation, const Vector3 &position)
      : rotation(rotation), position(position) {}

  ~Camera() = default;

  void UpdateCamera(float dt = 1.0f);

  Matrix4 BuildViewMatrix() const;

  inline const Vector3 &GetPosition() const { return position; };
  inline void SetPosition(const Vector3 &pos) { position = pos; };
  inline const Rotation &GetRotation() const { return rotation; };
  inline void SetRotation(const Rotation &rot) { rotation = rot; };

protected:
  Rotation rotation;
  Vector3 position;
};
