/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#include "Vectors.h"

#include <math.h>

Vector3 Vector3::Cross(const Vector3& v) const {
  return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

double Vector3::Dot(const Vector3& v) const {
  return x * v.x + y * v.y + z * v.z;
}

double Vector3::Magnitude() const { return sqrt(x * x + y * y + z * z); }

Vector3 Vector3::Normalized() const {
  double mag = Magnitude();
  if (mag == 0) return {0, 0, 0};
  return {x / mag, y / mag, z / mag};
}

void Vector3::Normalize() {
  double mag = Magnitude();
  if (mag == 0) return;
  x /= mag;
  y /= mag;
  z /= mag;
}
