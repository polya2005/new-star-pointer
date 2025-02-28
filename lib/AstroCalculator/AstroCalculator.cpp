/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#include "AstroCalculator.h"

#include <Arduino.h>

AstroCalculator& AstroCalculator::GetInstance() {
  static AstroCalculator instance;
  return instance;
}

void AstroCalculator::SetObserverLocation(float latitude, float longitude) {
  sin_latitude_ = sin(latitude);
  cos_latitude_ = cos(latitude);
  longitude_ = longitude;
}

EquatorialCoordinates AstroCalculator::HorizontalToEquatorial(float azimuth,
                                                              float altitude) {
  float cos_altitude = cos(altitude);
  float sin_altitude = sin(altitude);
  float cos_azimuth = cos(azimuth);
  float sin_dec =
      sin_latitude_ * sin_altitude + cos_latitude_ * cos_altitude * cos_azimuth;
  float cos_ha = (sin_altitude - sin_latitude_ * sin_dec) /
                 (cos_latitude_ * sqrt(1 - sin_dec * sin_dec));
  float dec = asin(sin_dec);
  float ha = acos(cos_ha);
  if (azimuth < PI) ha = TWO_PI - ha;
  float ra = lst_ - ha;
  if (ra < 0) ra += TWO_PI;
  return {ra, dec};
}

HorizontalCoordinates AstroCalculator::EquatorialToHorizontal(float ra,
                                                              float dec) {
  float ha = lst_ - ra;
  float sin_dec = sin(dec);
  float cos_dec = cos(dec);
  float sin_altitude =
      sin_latitude_ * sin_dec + cos_latitude_ * cos_dec * cos(ha);
  float cos_azimuth = (sin_dec - sin_latitude_ * sin_altitude) /
                      (cos_latitude_ * sqrt(1 - sin_altitude * sin_altitude));
  float altitude = asin(sin_altitude);
  float azimuth = acos(cos_azimuth);
  if (ha < PI) azimuth = TWO_PI - azimuth;
  return {azimuth, altitude};
}
