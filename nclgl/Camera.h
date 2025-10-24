#pragma once
#include "Frustum.h"
#include "Matrix4.h"
#include "Vector3.h"

namespace renderer {
  class Camera {
  public:
    struct Rotation {
      float pitch;
      float yaw;
    };

    inline Camera() : rotation({0.0, 0.0}), position({}) {}

    inline Camera(Rotation rotation, const Vector3& position)
        : rotation(rotation), position(position) {}

    ~Camera() = default;

    virtual void UpdateCamera(float dt);

    Matrix4 BuildViewMatrix() const;

    inline const Vector3& GetPosition() const { return position; };
    inline void SetPosition(const Vector3& pos) { position = pos; };
    inline const Rotation& GetRotation() const { return rotation; };
    inline void SetRotation(const Rotation& rot) { rotation = rot; };

    virtual const Frustum& GetFrustum() const = 0;

  protected:
    Rotation rotation;
    Vector3 position;
  };

  class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera(float nearPlane, float farPlane, float aspectRatio,
                      float fov);
    ~PerspectiveCamera() = default;

    void UpdateCamera(float dt) override;

    const Frustum& GetFrustum() const override { return m_frustum; };

  protected:
    Matrix4 m_projMatrix;
    Frustum m_frustum;
  };
} // namespace renderer
