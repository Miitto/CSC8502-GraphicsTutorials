#pragma once

#include "Matrix4.h"
#include "Plane.h"
#include "SceneNode.h"
#include <array>

class Frustum {
public:
  struct Planes {
    Plane n;
    Plane f;
    Plane left;
    Plane right;
    Plane top;
    Plane bottom;

    inline bool SphereInAllPlanes(const Vector3& centre, float radius) const {
      std::array<Plane, 6> planeArray = {n, f, left, right, top, bottom};
      for (const auto& plane : planeArray) {
        if (!plane.SphereInPlane(centre, radius)) {
          return false;
        }
      }
      return true;
    }
  };

  inline Frustum(const Matrix4& mat) {
    Vector3 x = {mat.values[0], mat.values[4], mat.values[8]};
    Vector3 y = {mat.values[1], mat.values[5], mat.values[9]};
    Vector3 z = {mat.values[2], mat.values[6], mat.values[10]};
    Vector3 w = {mat.values[3], mat.values[7], mat.values[11]};

    m_planes.right = {w - x, mat.values[15] - mat.values[12], true};
    m_planes.left = {w + x, mat.values[15] + mat.values[12], true};
    m_planes.bottom = {w + y, mat.values[15] + mat.values[13], true};
    m_planes.top = {w - y, mat.values[15] - mat.values[13], true};
    m_planes.f = {w - z, mat.values[15] - mat.values[14], true};
    m_planes.n = {w + z, mat.values[15] + mat.values[14], true};
  }
  ~Frustum() = default;

  inline bool SphereInFrustum(const Vector3& centre, float radius) const {
    return m_planes.SphereInAllPlanes(centre, radius);
  }

  inline bool NodeInFrustum(const renderer::scene::Node& node) const {
    return SphereInFrustum(node.GetTransforms().world.GetPositionVector(),
                           node.GetBoundingRadius());
  }

protected:
  Planes m_planes;
};
