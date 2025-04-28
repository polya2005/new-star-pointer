/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_DATATYPES_DATATYPES_H_
#define LIB_DATATYPES_DATATYPES_H_

/**
 * @brief The horizontal coordinates of an object in the sky.
 */
typedef struct {
  /**
   * @brief The azimuth angle in radians.
   *
   * The azimuth angle is the angle between the object and the north direction,
   * measured clockwise, that is, 0 is the north, PI/2 is the east, PI is the
   * south, and 3*PI/2 is the west.
   */
  double azimuth;

  /**
   * @brief The altitude angle in radians.
   *
   * The altitude angle is the angle between the object and the horizon, that
   * is, 0 is the horizon, PI/2 is the zenith, and -PI/2 is the nadir.
   */
  double altitude;
} HorizontalCoordinates;

/**
 * @brief The equatorial coordinates of an object in the sky.
 */
typedef struct {
  /**
   * @brief The right ascension angle in radians.
   *
   * The right ascension angle is the angle between the object and the vernal
   * equinox, measured eastward. It is more commonly expressed in hours,
   * minutes, and seconds, but here we use radians.
   */
  double ra;

  /**
   * @brief The declination angle in radians.
   *
   * The declination angle is the angle between the object and the celestial
   * equator, measured northward, that is, 0 is the celestial equator, PI/2 is
   * the north celestial pole, and -PI/2 is the south celestial pole.
   */
  double dec;
} EquatorialCoordinates;

/**
 * @brief The observer's location on the Earth.
 *
 * The observer's location is defined by its latitude and longitude. The
 * latitude is the angle between the object and the equator, measured northward,
 * that is, 0 is the equator, PI/2 is the north pole, and -PI/2 is the south
 * pole. The longitude is the angle between the object and the prime meridian,
 * measured eastward, that is, 0 is the prime meridian, PI/2 is the 90th
 * meridian east, PI is the 180th meridian, and -PI/2 is the 90th meridian
 * west.
 */
typedef struct {
  /**
   * @brief The latitude in radians.
   *
   * The latitude is the angle between the object and the equator, measured
   * northward, that is, 0 is the equator, PI/2 is the north pole, and -PI/2 is
   * the south pole.
   */
  double latitude;

  /**
   * @brief The longitude in radians.
   *
   * The longitude is the angle between the object and the prime meridian,
   * measured eastward, that is, 0 is the prime meridian, PI/2 is the 90th
   * meridian east, PI is the 180th meridian, and -PI/2 is the 90th meridian
   * west.
   */
  double longitude;

  /**
   * @brief The validity of the location.
   */
  bool is_valid;
} ObserverLocation;

#endif  // LIB_DATATYPES_DATATYPES_H_
