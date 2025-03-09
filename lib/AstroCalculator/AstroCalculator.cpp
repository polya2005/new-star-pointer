/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#include "AstroCalculator.h"

#include <Arduino.h>

AstroCalculator& AstroCalculator::GetInstance() {
  static AstroCalculator instance;
  return instance;
}

void AstroCalculator::SetObserverLocation(double latitude, double longitude) {
  sin_latitude_ = sin(latitude);
  cos_latitude_ = cos(latitude);
  longitude_ = longitude;
}

EquatorialCoordinates AstroCalculator::HorizontalToEquatorial(double azimuth,
                                                              double altitude) {
  double cos_altitude = cos(altitude);
  double sin_altitude = sin(altitude);
  double cos_azimuth = cos(azimuth);
  double sin_dec =
      sin_latitude_ * sin_altitude + cos_latitude_ * cos_altitude * cos_azimuth;
  double cos_ha = (sin_altitude - sin_latitude_ * sin_dec) /
                  (cos_latitude_ * sqrt(1 - sin_dec * sin_dec));
  double dec = asin(sin_dec);
  double ha = acos(cos_ha);
  if (azimuth < PI) ha = TWO_PI - ha;
  double ra = lst_ - ha;
  if (ra < 0) ra += TWO_PI;
  return {ra, dec};
}

HorizontalCoordinates AstroCalculator::EquatorialToHorizontal(double ra,
                                                              double dec) {
  double ha = lst_ - ra;
  double sin_dec = sin(dec);
  double cos_dec = cos(dec);
  double sin_altitude =
      sin_latitude_ * sin_dec + cos_latitude_ * cos_dec * cos(ha);
  double cos_azimuth = (sin_dec - sin_latitude_ * sin_altitude) /
                       (cos_latitude_ * sqrt(1 - sin_altitude * sin_altitude));
  double altitude = asin(sin_altitude);
  double azimuth = acos(cos_azimuth);
  if (ha < PI) azimuth = TWO_PI - azimuth;
  return {azimuth, altitude};
}
