/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#include "MovementController.h"

#define DEBUG

#include <TempDebug.h>

int32_t MovementController::AzimuthToSteps(double azimuth) {
  return static_cast<int32_t>(azimuth * steps_per_radian_az_);
}

int32_t MovementController::AltitudeToSteps(double altitude) {
  return static_cast<int32_t>(altitude * steps_per_radian_al_);
}

MovementController& MovementController::GetInstance() {
  static MovementController instance;
  return instance;
}

void MovementController::AttachAzimuthMotor(uint8_t step_pin, uint8_t dir_pin,
                                            double steps_per_radian) {
  az_ = new AccelStepper(AccelStepper::DRIVER, step_pin, dir_pin);
  steps_per_radian_az_ = steps_per_radian;
}

void MovementController::AttachAltitudeMotor(uint8_t step_pin, uint8_t dir_pin,
                                             double steps_per_radian) {
  al_ = new AccelStepper(AccelStepper::DRIVER, step_pin, dir_pin);
  steps_per_radian_al_ = steps_per_radian;
}

bool MovementController::MoveTo(double azimuth, double altitude) {
  if (altitude >= 0 && altitude <= HALF_PI) {
    az_->moveTo(AzimuthToSteps(azimuth));
    al_->moveTo(AltitudeToSteps(altitude));
    return true;
  }
  return false;
}

void MovementController::SetCurrentPosition(double azimuth, double altitude) {
  az_->setCurrentPosition(AzimuthToSteps(azimuth));
  al_->setCurrentPosition(AltitudeToSteps(altitude));
}

double MovementController::GetCurrentAzimuth() const {
  return az_->currentPosition() / steps_per_radian_az_;
}

double MovementController::GetCurrentAltitude() const {
  return al_->currentPosition() / steps_per_radian_al_;
}

void MovementController::SetJogStepAngle(double angle) {
  jog_steps_az_ = AzimuthToSteps(angle);
  jog_steps_al_ = AltitudeToSteps(angle);
}

void MovementController::JogEast() {
  az_->move(jog_steps_az_);
  debugln("Jogging East");
}

void MovementController::JogWest() {
  az_->move(-jog_steps_az_);
  debugln("Jogging West");
}

void MovementController::JogUp() {
  if (al_->targetPosition() < HALF_PI) {
    al_->move(jog_steps_al_);
    debugln("Jogging Up");
  }
}

void MovementController::JogDown() {
  if (al_->targetPosition() > 0) {
    al_->move(-jog_steps_al_);
    debugln("Jogging Down");
  }
}

bool MovementController::Run() { return az_->run() || al_->run(); }

void MovementController::Stop() {
  az_->stop();
  al_->stop();
  while (Run()) {
  }  // decelerate to stop
}

MovementController::~MovementController() {
  delete az_;
  delete al_;
}
