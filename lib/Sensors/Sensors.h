/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_SENSORS_SENSORS_H_
#define LIB_SENSORS_SENSORS_H_

#include "Adafruit_ADXL345_U.h"
#include "DFRobot_QMC5883.h"
#include "Vectors.h"

/**
 * @brief A class that provides access to various sensors.
 *
 * The Sensors class provides access to various sensors, such as the
 * accelerometer, magnetometer, and GPS. Think of this class as an abstraction
 * layer that hides the details of the sensors from the rest of the program.
 * The class provides methods to read data from the sensors and to calibrate
 * the sensors.
 *
 * The implementation assumes that the accelerometer is an ADXL345 and the
 * magnetometer is a QMC5883. Both of those sensors are connected to the I2C
 * bus. The GPS module is assumed to be connected to UART0.
 */
class Sensors {
 private:
  Adafruit_ADXL345_Unified accel;
  DFRobot_QMC5883 compass;
  SerialUART& gps;

  Sensors() : gps(Serial1) {}
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
