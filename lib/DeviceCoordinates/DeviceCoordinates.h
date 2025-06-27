/**
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */
#ifndef LIB_DEVICECOORDINATES_DEVICECOORDINATES_H_
#define LIB_DEVICECOORDINATES_DEVICECOORDINATES_H_

#include <AstroCalculator.h>
#include <Datatypes.h>
#include <Matrices.h>
#include <Vectors.h>

#include <utility>  // for std::pair

/**
 * @brief A class that represents device coordinates and provides functions to
 * convert between device coordinates and horizontal coordinates.
 *
 * The class provides functions to convert between device coordinates and
 * horizontal coordinates. The device coordinates are defined by the azimuth and
 * altitude angles, both in radians and measured at the motors. The horizontal
 * coordinates are defined by the azimuth and altitude angles, both in radians.
 *
 * The class depends on the singleton instance of the AstroCalculator class to
 * convert between device coordinates and horizontal coordinates.
 * **The AstroCalculator instance must be given the coordinates and current time
 * before setting the calibration data.**
 */
class DeviceCoordinates {
 private:
  static const AstroCalculator& astro_calculator_;
  static Matrix3 device_to_horizontal_,
      horizontal_to_device_;  // The transformation matrices
  /**
   * @brief Helper function to convert azimuth and altitude angles to a Vector3
   *
   * This function converts the azimuth and altitude angles in radians to a
   * Vector3 object representing the direction in corresponding coordinates.
   *
   * @param azimuth The azimuth angle in radians.
   * @param altitude The altitude angle in radians.
   * @return Vector3 The direction vector in device coordinates.
   */
  static Vector3 AzimuthAltitudeToVector3(double azimuth, double altitude);

  /**
   * @brief Helper function to convert a Vector3 to azimuth and altitude angles
   *
   * This function converts a Vector3 object representing a direction into the
   * azimuth and altitude angles in radians.
   *
   * @param v The direction vector.
   *
   * @return std::pair<double, double> A pair containing the azimuth and
   * altitude angles in radians.
   */
  static std::pair<double, double> Vector3ToAzimuthAltitude(const Vector3& v);

 public:
  double d_azimuth;   // The azimuth angle in radians.
  double d_altitude;  // The altitude angle in radians.

  /**
   * @brief Sets the calibration data for the device coordinates.
   *
   * @param g The gravity vector in device coordinates.
   * @param b The magnetic field vector in device coordinates.
   *
   * @note The AstroCalculator instance must be given the coordinates and
   * current time before setting the calibration data.
   */
  static void SetCalibrationData(const Vector3& g, const Vector3& b);

  /**
   * @brief Default constructor for DeviceCoordinates.
   *
   * Initializes the azimuth and altitude angles to 0.
   */
  DeviceCoordinates() : d_azimuth(0), d_altitude(0) {}

  /**
   * @brief Constructor for DeviceCoordinates with specified azimuth and
   * altitude.
   *
   * Initializes the azimuth and altitude angles to the specified values.
   * @param azimuth The azimuth angle in radians.
   * @param altitude The altitude angle in radians.
   */
  DeviceCoordinates(double azimuth, double altitude)
      : d_azimuth(azimuth), d_altitude(altitude) {}

  /**
   * @brief Copy constructor for DeviceCoordinates.
   *
   * @param other The DeviceCoordinates object to copy.
   */
  DeviceCoordinates(const DeviceCoordinates& other)
      : d_azimuth(other.d_azimuth), d_altitude(other.d_altitude) {}

  /**
   * @brief Assignment operator for DeviceCoordinates.
   *
   * @param other The DeviceCoordinates object to assign.
   * @return DeviceCoordinates& A reference to this DeviceCoordinates object.
   */
  DeviceCoordinates& operator=(const DeviceCoordinates& other) {
    if (this != &other) {
      d_azimuth = other.d_azimuth;
      d_altitude = other.d_altitude;
    }
    return *this;
  }

  /**
   * @brief Converts a HorizontalCoordinates object to DeviceCoordinates.
   *
   * This constructor converts the azimuth and altitude angles in horizontal
   * coordinates to a DeviceCoordinates object representing the device
   * coordinates.
   *
   * @param hc The HorizontalCoordinates object to convert.
   */
  explicit DeviceCoordinates(const HorizontalCoordinates& hc);

  /**
   * @brief Converts the device coordinates to horizontal coordinates.
   *
   * This function converts the azimuth and altitude angles in device
   * coordinates to a HorizontalCoordinates object representing the horizontal
   * coordinates.
   *
   * @return HorizontalCoordinates The horizontal coordinates corresponding to
   * the device coordinates.
   */
  HorizontalCoordinates ToHorizontalCoordinates() const;
};

#endif  // LIB_DEVICECOORDINATES_DEVICECOORDINATES_H_
