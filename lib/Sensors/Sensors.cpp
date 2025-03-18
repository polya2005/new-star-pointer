/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#include "Sensors.h"

#include "Adafruit_ADXL345_U.h"
#include "Adafruit_Sensor.h"
#include "Arduino.h"
#include "TempDebug.h"
#include "Wire.h"

Sensors& Sensors::GetInstance() {
  static Sensors instance;
  return instance;
}

void Sensors::Init() {
  accel = Adafruit_ADXL345_Unified(12345);
  if (!accel.begin()) {
    debugln("Could not find a valid ADXL345 sensor, check wiring!");
    while (1) {
    }
  }
  accel.setRange(ADXL345_RANGE_2_G);
}

Vector3 Sensors::ReadAcceleration() {
  sensors_event_t event;
  accel.getEvent(&event);
  return {event.acceleration.x, event.acceleration.y, event.acceleration.z};
}
