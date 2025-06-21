/**
 * copyright (c) 2025 Boonyakorn Thanpanit
 */
#include "DeviceCoordinates.h"

#include <AstroCalculator.h>
#include <math.h>

#include <utility>  // for std::pair

const AstroCalculator& DeviceCoordinates::astro_calculator_ =
    AstroCalculator::GetInstance();
Matrix3 DeviceCoordinates::device_to_horizontal_;
Matrix3 DeviceCoordinates::horizontal_to_device_;

void DeviceCoordinates::SetCalibrationData(const Vector3& g, const Vector3& b) {
  Vector3 h_b_horizontal_normalized =
      astro_calculator_.EarthFrameNormalizedMagneticField();
  Matrix3 h_knowns = Matrix3(
      Vector3(0, 0, -1), h_b_horizontal_normalized,
      Vector3(h_b_horizontal_normalized.y, -h_b_horizontal_normalized.x, 0));

  Vector3 d_g_normalized = g.Normalized();
  Vector3 d_b_horizontal_normalized =
      (b - d_g_normalized * d_g_normalized.Dot(b)).Normalized();
  Matrix3 d_knowns = Matrix3(d_g_normalized, d_b_horizontal_normalized,
                             d_g_normalized.Cross(d_b_horizontal_normalized));

  // device_to_horizontal * d_knowns = h_knowns
  device_to_horizontal_ =
      h_knowns * d_knowns.Transposed();  // d_knowns is orthogonal
  horizontal_to_device_ = device_to_horizontal_.Transposed();
}

Vector3 DeviceCoordinates::AzimuthAltitudeToVector3(double azimuth,
                                                    double altitude) {
  // Convert azimuth and altitude to a direction vector in device coordinates
  double cos_altitude = cos(altitude);
  return Vector3(cos_altitude * sin(azimuth), cos_altitude * cos(azimuth),
                 sin(altitude));
}

std::pair<double, double> DeviceCoordinates::Vector3ToAzimuthAltitude(
    const Vector3& v) {
  double azimuth = atan2(v.x, v.y);
  double altitude = atan2(v.z, sqrt(v.x * v.x + v.y * v.y));
  return std::make_pair(azimuth, altitude);
}

DeviceCoordinates::DeviceCoordinates(const HorizontalCoordinates& hc) {
  const Vector3 h_v = AzimuthAltitudeToVector3(hc.azimuth, hc.altitude);
  const Vector3 d_v = horizontal_to_device_ * h_v;
  std::pair<double, double> az_alt = Vector3ToAzimuthAltitude(d_v);
  d_azimuth = az_alt.first;
  d_altitude = az_alt.second;
}

HorizontalCoordinates DeviceCoordinates::ToHorizontalCoordinates() const {
  Vector3 d_v = AzimuthAltitudeToVector3(d_azimuth, d_altitude);
  Vector3 h_v = device_to_horizontal_ * d_v;
  std::pair<double, double> az_alt = Vector3ToAzimuthAltitude(h_v);
  return HorizontalCoordinates{az_alt.first, az_alt.second};
}
