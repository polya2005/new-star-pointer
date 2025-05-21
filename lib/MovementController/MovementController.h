/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_MOVEMENTCONTROLLER_MOVEMENTCONTROLLER_H_
#define LIB_MOVEMENTCONTROLLER_MOVEMENTCONTROLLER_H_

#include <AccelStepper.h>

/**
 * @brief A class that controls the movement of the pointer.
 *
 * The class controls the movement of the pointer by controlling the azimuth
 * and altitude motors. The angles are specified in radians and are measured
 * with respect to the device's, as opposed to the observer's, north and
 * zenith. The azimuth angle is measured eastward from the north, and the
 * altitude angle is measured up from the horizon.
 *
 * The class is a singleton class.
 *
 */
class MovementController {
 private:
  /**
   * The altitude motor.
   */
  AccelStepper* al_;
  /**
   * The azimuth motor.
   */
  AccelStepper* az_;
  /**
   * The number of steps per radian east.
   */
  double steps_per_radian_az_;
  /**
   * The number of steps per radian up.
   */
  double steps_per_radian_al_;
  /**
   * The number of steps to jog east.
   */
  int16_t jog_steps_az_;
  /**
   * The number of steps to jog up.
   */
  int16_t jog_steps_al_;

  /**
   * Converts the azimuth angle in radians to the number of steps.
   *
   * @param azimuth The azimuth angle in radians.
   * @return int32_t The number of steps.
   */
  int32_t AzimuthToSteps(double azimuth);
  /**
   * Converts the altitude angle in radians to the number of steps.
   *
   * @param altitude The altitude angle in radians.
   * @return int32_t The number of steps.
   */
  int32_t AltitudeToSteps(double altitude);

  MovementController() {}
  MovementController(const MovementController& other) = delete;
  void operator=(const MovementController& other) = delete;

 public:
  /**
   * @brief Gets the instance of the MovementController class.
   *
   * @return MovementController& The instance of the MovementController class.
   */
  static MovementController& GetInstance();

  /**
   * @brief Attaches the azimuth motor to the controller.
   *
   * Specifies the step pin, dir pin, and the number of steps per radian east.
   * A negative step number reverses the direction.
   *
   * @param step_pin The step pin.
   * @param dir_pin The dir pin.
   * @param steps_per_radian The number of steps per radian east.
   */
  void AttachAzimuthMotor(uint8_t step_pin, uint8_t dir_pin,
                          double steps_per_radian);

  /**
   * @brief Attaches the altitude motor to the controller.
   *
   * Specifies the step pin, dir pin, and the number of steps per radian up.
   * A negative step number reverses the direction.
   *
   * @param step_pin The step pin.
   * @param dir_pin The dir pin.
   * @param steps_per_radian The number of steps per radian up.
   */
  void AttachAltitudeMotor(uint8_t step_pin, uint8_t dir_pin,
                           double steps_per_radian);

  // Moves to the specified azimuth and altitude, both in radians, if the
  // altitude is between 0 and PI/2 and returns true. If the altitude is
  // outside the range, returns false.
  /**
   * @brief Moves the pointer to the specified azimuth and altitude.
   *
   * Moves the pointer to the specified azimuth and altitude, both in radians.
   *
   * @param azimuth The azimuth in radians.
   * @param altitude The altitude in radians.
   * @return true if the altitude is between 0 and PI/2.
   * @return false otherwise.
   */
  bool MoveTo(double azimuth, double altitude);

  /**
   * @brief Marks the current position as the specified azimuth and altitude.
   *
   * Marks the current position as the specified azimuth and altitude, both in
   * radians.
   *
   * @param azimuth The current azimuth in radians.
   * @param altitude The current altitude in radians.
   */
  void SetCurrentPosition(double azimuth, double altitude);

  /**
   * @brief Sets the angle to move the motor in one jogging step.
   *
   * Specifies the approximate angle to move the motor in one jogging step in
   * radians.
   *
   * @param angle The angle in radians.
   */
  void SetJogStepAngle(double angle);
  /**
   * @brief Jogs to east once.
   */
  inline void JogEast();

  /**
   * @brief Jogs to west once.
   */
  inline void JogWest();

  /**
   * @brief Jogs up once if the pointer is not past the zenith.
   */
  void JogUp();

  /**
   * @brief Jogs down once if the pointer is above the horizon.
   */
  void JogDown();

  /**
   * @brief Executes the movements.
   *
   * Executes the movements. Must be called repeatedly to move the pointer.
   *
   * @return true if the motion is in progress.
   * @return false otherwise.
   */
  inline bool Run();

  /**
   * @brief Stops the movements.
   */
  void Stop();

  ~MovementController();
};

#endif  // LIB_MOVEMENTCONTROLLER_MOVEMENTCONTROLLER_H_
