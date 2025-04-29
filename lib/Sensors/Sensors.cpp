/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#include "Sensors.h"

#include "Adafruit_ADXL345_U.h"
#include "Adafruit_Sensor.h"
#include "Arduino.h"
#include "DFRobot_QMC5883.h"
#include "Datatypes.h"
#include "TempDebug.h"
#include "TinyGPSPlus.h"
#include "Wire.h"

Sensors& Sensors::GetInstance() {
  static Sensors instance;
  return instance;
}

void Sensors::Init(SerialUART* gpsSerial = &Serial1) {
  this->gpsSerial = *gpsSerial;
  accel = Adafruit_ADXL345_Unified(12345);
  if (!accel.begin()) {
    debugln("Could not find a valid ADXL345 sensor, check wiring!");
    while (1) {
    }
  }
  compass = DFRobot_QMC5883(&Wire, QMC5883_ADDRESS);
  if (!compass.begin()) {
    debugln("Could not find a valid QMC5883 sensor, check wiring!");
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

Vector3 Sensors::ReadMagneticField() {
  sVector_t v = compass.readRaw();
  return {v.XAxis, v.YAxis, v.ZAxis};
}

ObserverLocation Sensors::ReadObserverLocation(uint32_t timeout = 2000ul) {
  ObserverLocation location{};
  uint32_t start = millis();
  while (millis() - start < timeout) {
    while (gpsSerial.available()) {
      gps.encode(gpsSerial.read());
      if (gps.location.isValid()) {
        location.latitude = radians(gps.location.lat());
        location.longitude = radians(gps.location.lng());
        location.is_valid = true;
        return location;
      }
    }
  }
  return location;  // Return invalid location if timeout
}

double Sensors::ReadJulianDate() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
  if (gps.date.isValid() && gps.time.isValid()) {
    int32_t year = gps.date.year();
    int32_t month = gps.date.month();
    int32_t day = gps.date.day();
    double dayFraction =
        (gps.time.hour() * 3600 + gps.time.minute() * 60 + gps.time.second()) /
        86400.0;
    if (month < 3) {
      year--;
      month += 12;
    }
    int32_t a = year / 100;
    int32_t b = 2 - a + a / 4;
    int32_t integerPart =
        (year + 4716) * 1461 / 4 + (month + 1) * 153 / 5 + day + b;
    return integerPart - 1524.5 + dayFraction;
  }
  return 0.0;  // Return 0 if date or time is invalid
}
