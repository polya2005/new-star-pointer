/**
 * copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_MATRICES_MATRICES_H_
#define LIB_MATRICES_MATRICES_H_

#include <Vectors.h>

/**
 * @brief A 3x3 matrix.
 */
class Matrix3 {
 private:
  Vector3 columns_[3];  // The columns of the matrix.

 public:

  /**
   * @brief Default constructor for Matrix3.
   *
   * Initializes the matrix to the identity matrix.
   */
  Matrix3();
  
  /**
   * @brief Constructor for Matrix3.
   *
   * @param c1 The first column of the matrix.
   * @param c2 The second column of the matrix.
   * @param c3 The third column of the matrix.
   */
  Matrix3(const Vector3& c1, const Vector3& c2, const Vector3& c3);

  /**
   * @brief Copy constructor for Matrix3.
   * 
   * @param m The matrix to copy.
   */
  Matrix3(const Matrix3& m);

  /**
   * @brief Copy assignment operator for Matrix3.
   * 
   * @param m The matrix to assign.
   * @return Matrix3& A reference to this matrix.
   */
  Matrix3& operator=(const Matrix3& m);

  /**
   * @brief Multiplies this matrix with a vector.
   *
   * This function multiplies the matrix with a vector and returns the resulting
   * vector. The multiplication is defined as usual matrix-vector
   * multiplication.
   *
   * @param v The vector to multiply with.
   *
   * @return Vector3 The resulting vector after multiplication.
   */
  Vector3 operator*(const Vector3& v) const;

  /**
   * @brief Multiplies this matrix with another matrix.
   *
   * This function multiplies the matrix with another matrix and returns the
   * resulting matrix. The multiplication is defined as usual matrix-matrix
   * multiplication.
   *
   * @param m The matrix to multiply with.
   *
   * @return Matrix3 The resulting matrix after multiplication.
   */
  Matrix3 operator*(const Matrix3& m) const;

  /**
   * @brief Transposes the matrix.
   * 
   * This function transposes the matrix and returns a new matrix with the
   * transposed values. Does not modify the original matrix. 
   * 
   * @return Matrix3 The transposed matrix
   */
  Matrix3 Transposed() const;
};

#endif  // LIB_MATRICES_MATRICES_H_
