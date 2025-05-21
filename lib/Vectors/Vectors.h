/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_VECTORS_VECTORS_H_
#define LIB_VECTORS_VECTORS_H_

/**
 * @brief A 3d vector.
 *
 */
class Vector3 {
 public:
  /**
   * @brief The x component of the vector.
   */
  double x;

  /**
   * @brief The y component of the vector.
   */
  double y;

  /**
   * @brief The z component of the vector.
   */
  double z;

  /**
   * @brief Computes the cross product of this vector and another vector.
   *
   * @param v The other vector.
   * @return Vector3 The cross product of this vector and the other vector.
   */
  Vector3 Cross(const Vector3& v) const;

  /**
   * @brief Computes the magnitude of the vector.
   *
   * @return double The magnitude of the vector.
   */
  double Magnitude() const;

  /**
   * @brief Computes the normalized vector.
   *
   * Normalizes the vector and returns a new vector with the same direction.
   * Does not modify the original vector.
   *
   * @return Vector3 The normalized vector.
   * @see Normalize()
   */
  Vector3 Normalized() const;

  /**
   * @brief Normalizes the vector.
   *
   * Normalizes the vector in place.
   *
   */
  void Normalize();
};

#endif  // LIB_VECTORS_VECTORS_H_
