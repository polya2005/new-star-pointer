/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_SENSORS_SENSORS_H_
#define LIB_SENSORS_SENSORS_H_

#include "Adafruit_ADXL345_U.h"
#include "Vectors.h"

/**
 * @brief A class that provides access to various sensors.
 *
 * The Sensors class provides access to various sensors, such as the
 * accelerometer, magnetometer, and GPS. The class provides methods to read
 * data from the sensors and to calibrate the sensors.
 */
class Sensors {
 private:
  Adafruit_ADXL345_Unified accel;

  Sensors() {}
  Sensors(const Sensors&) = delete;
  void operator=(const Sensors&) = delete;

 public:
  /**
   * @brief Gets the singleton instance of the Sensors class.
   *
   * @return Sensors& The singleton instance.
   */
  static Sensors& GetInstance();

  /**
   * @brief Initializes the sensors.
   *
   */
  void Init();

  /**
   * @brief Reads the acceleration from the accelerometer.
   * Reads the acceleration from the accelerometer and returns it as a 3d
   * vector. Must call Init() before calling this method for the first time.
   *
   * @return Vector3 The acceleration vector.
   */
  Vector3 ReadAcceleration();

  /**
   * @brief Reads the magnetic field from the magnetometer.
   *
   * @return Vector3 The magnetic field vector.
   */
  Vector3 ReadMagneticField();
};

#endif  // LIB_SENSORS_SENSORS_H_
