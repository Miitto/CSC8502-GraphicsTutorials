#pragma once

#include "Vector3.h"

class Plane {
public:
  Plane() = default;
  inline Plane(const Vector3& normal, float d, bool normalize = false) {
    if (normalize) {
      float length = normal.Length();
      this->normal = normal / length;
      this->d = d / length;
    } else {
      this->normal = normal;
      this->d = d;
    }
  }
  ~Plane() = default;

  inline void SetNormal(const Vector3& normal) { this->normal = normal; }
  inline const Vector3& GetNormal() const { return normal; }
  inline void SetDistance(float d) { this->d = d; }
  inline float GetDistance() const { return d; }

  inline bool SphereInPlane(const Vector3& center, float radius) const {
    auto distance = Vector3::Dot(normal, center) + d;

    return distance + radius >= 0;
  }

protected:
  Vector3 normal;
  float d;
};
