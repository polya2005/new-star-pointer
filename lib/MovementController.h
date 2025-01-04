/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_MOVEMENTCONTROLLER_H_
#define LIB_MOVEMENTCONTROLLER_H_

#include <AccelStepper.h>

class MovementController {
 private:
  AccelStepper *al_, *az_;
  float steps_per_radian_az_, steps_per_radian_al_;
  int16_t jog_steps_az_, jog_steps_al_;

  int32_t AzimuthToSteps(float azimuth);
  int32_t AltitudeToSteps(float altitude);

  MovementController() {}
  MovementController(const MovementController& other) = delete;
  void operator=(const MovementController& other) = delete;
  static MovementController* instance_;

 public:
  // Returns the instance of the MovementController class
  static MovementController* GetInstance();

  // Specifies the step pin, dir pin, and the number of steps per radian east.
  // A negative step number reverses the direction.
  void AttachAzimuthMotor(uint8_t step_pin, uint8_t dir_pin,
                          float steps_per_radian);

  // Specifies the step pin, dir pin, and the number of steps per radian up.
  // A negative step number reverses the direction.
  void AttachAltitudeMotor(uint8_t step_pin, uint8_t dir_pin,
                           float steps_per_radian);

  // Moves to the specified azimuth and altitude, both in radians, if the
  // altitude is between 0 and PI/2 and returns true. If the altitude is
  // outside the range, returns false.
  bool MoveTo(float azimuth, float altitude);

  // Marks the current position as the specified azimuth and altitude,
  // both in radians.
  void SetCurrentPosition(float azimuth, float altitude);

  // Specifies the approximate angle to move the motor in one jogging step
  // in radians.
  void SetJogStepAngle(float angle);

  // Jogs to east once.
  void JogEast();

  // Jogs to west once.
  void JogWest();

  // Jogs up once if the pointer has not passed zenith.
  void JogUp();

  // Jogs down once if the pointer is above the horizon.
  void JogDown();

  // Executes the movements. Returns true if the motion is in progress and
  // false otherwise.
  bool Run();

  // Stops all the movements.
  void Stop();

  ~MovementController();
};

MovementController* MovementController::instance_ = nullptr;

#endif  // LIB_MOVEMENTCONTROLLER_H_
