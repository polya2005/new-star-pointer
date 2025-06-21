/**
 * copyright (c) 2025 Boonyakorn Thanpanit
 */

#include "Matrices.h"

Matrix3::Matrix3() {
  // Initialize to identity matrix
  columns_[0] = Vector3(1, 0, 0);
  columns_[1] = Vector3(0, 1, 0);
  columns_[2] = Vector3(0, 0, 1);
}

Matrix3::Matrix3(const Vector3& c1, const Vector3& c2, const Vector3& c3) {
  columns_[0] = c1;
  columns_[1] = c2;
  columns_[2] = c3;
}

Matrix3::Matrix3(const Matrix3& m) {
  columns_[0] = m.columns_[0];
  columns_[1] = m.columns_[1];
  columns_[2] = m.columns_[2];
}

Matrix3& Matrix3::operator=(const Matrix3& m) {
  if (this != &m) {
    columns_[0] = m.columns_[0];
    columns_[1] = m.columns_[1];
    columns_[2] = m.columns_[2];
  }
  return *this;
}

Vector3 Matrix3::operator*(const Vector3& v) const {
  return v.x * columns_[0] + v.y * columns_[1] + v.z * columns_[2];
}

Matrix3 Matrix3::operator*(const Matrix3& m) const {
  return Matrix3(*this * m.columns_[0], *this * m.columns_[1],
                 *this * m.columns_[2]);
}

Matrix3 Matrix3::Transposed() const {
  return Matrix3(Vector3(columns_[0].x, columns_[1].x, columns_[2].x),
                 Vector3(columns_[0].y, columns_[1].y, columns_[2].y),
                 Vector3(columns_[0].z, columns_[1].z, columns_[2].z));
}
