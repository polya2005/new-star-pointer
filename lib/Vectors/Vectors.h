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
   * @brief Default constructor for Vector3.
   * Initializes the vector to (0, 0, 0).
   */
  Vector3() : x(0), y(0), z(0) {}

  /**
   * @brief Constructor for Vector3 with specified components.
   *
   * @param x The x component of the vector.
   * @param y The y component of the vector.
   * @param z The z component of the vector.
   */
  Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

  /**
   * @brief Copy constructor for Vector3.
   *
   * @param v The vector to copy.
   */
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

  /**
   * @brief Assignment operator for Vector3.
   *
   * @param v The vector to assign.
   * @return Vector3& A reference to this vector.
   */
  Vector3& operator=(const Vector3& v) {
    if (this != &v) {
      x = v.x;
      y = v.y;
      z = v.z;
    }
    return *this;
  }

  /**
   * @brief Computes the cross product of this vector and another vector.
   *
   * @param v The other vector.
   * @return Vector3 The cross product of this vector and the other vector.
   */
  Vector3 Cross(const Vector3& v) const;

  /**
   * @brief Computes the dot product of this vector and another vector.
   *
   * @param v The other vector.
   * @return double The dot product of this vector and the other vector.
   */
  double Dot(const Vector3& v) const;

  /**
   * @brief multiplies this vector by a scalar.
   *
   * @param scalar The scalar to multiply with.
   * @return Vector3 The resulting vector after multiplication.
   */
  inline Vector3 operator*(double scalar) const {
    return {x * scalar, y * scalar, z * scalar};
  }

  /**
   * @see operator*(double scalar)
   *
   * @param scalar
   * @param v
   * @return Vector3
   */
  friend inline Vector3 operator*(double scalar, const Vector3& v) {
    return {v.x * scalar, v.y * scalar, v.z * scalar};
  }

  /**
   * @brief Adds another vector to this vector.
   *
   * @param v The vector to add.
   * @return Vector3 The resulting vector after addition.
   */
  inline Vector3 operator+(const Vector3& v) const {
    return {x + v.x, y + v.y, z + v.z};
  }

  /**
   * @brief Subtracts another vector from this vector.
   *
   * @param v The vector to subtract.
   * @return Vector3 The resulting vector after subtraction.
   */
  inline Vector3 operator-(const Vector3& v) const {
    return {x - v.x, y - v.y, z - v.z};
  }

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
