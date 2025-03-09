/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_ASTROCALCULATOR_ASTROCALCULATOR_H_
#define LIB_ASTROCALCULATOR_ASTROCALCULATOR_H_

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
 * @brief A class that calculates the positions of celestial objects.
 *
 * The class calculates the positions of celestial objects based on the
 * observer's location and the current time. The observer's location is
 * specified by the latitude and longitude, both in radians. The current time
 * is specified by the Julian date, which is the number of days since the
 * beginning of the Julian period, which started on January 1, 4713 BC.
 *
 * The class is a singleton class.
 */
class AstroCalculator {
 private:
  /**
   * @brief The sine of the observer's latitude.
   */
  double sin_latitude_;
  /**
   * @brief The cosine of the observer's latitude.
   */
  double cos_latitude_;
  /**
   * @brief The observer's longitude in radians.
   */
  double longitude_;
  /**
   * @brief The local sidereal time in radians.
   *
   * The local sidereal time is defined as the sum of the right ascension and
   * the hour angle of any point on the celestial sphere. It is more commonly
   * expressed in hours, minutes, and seconds, but here we use radians. This
   * should not be confused with the local mean time, which is the time measured
   * by a clock.
   */
  double lst_;  // in radians

  AstroCalculator() {}
  AstroCalculator(const AstroCalculator& other) = delete;
  void operator=(const AstroCalculator& other) = delete;

 public:
  /**
   * @brief Gets the singleton instance of the AstroCalculator class.
   *
   * @return AstroCalculator& The singleton instance.
   */
  static AstroCalculator& GetInstance();

  /**
   * @brief Sets the observer location
   *
   * @param latitude The observer's latitude in radians.
   * @param longitude The observer's longitude in radians.
   */
  void SetObserverLocation(double latitude, double longitude);

  /**
   * @brief Converts the given horizontal coordinates into equatorial
   * coordinates.
   *
   * Converts the given horizontal coordinates into equatorial coordinates. The
   * results will change over time as the Earth rotates. Therefore, the
   * UpdateLst() function should be called before calling this function.
   *
   * @param azimuth The azimuth angle in radians.
   * @param altitude The altitude angle in radians.
   * @return EquatorialCoordinates
   */
  EquatorialCoordinates HorizontalToEquatorial(double azimuth, double altitude);

  /**
   * @brief Converts the given equatorial coordinates into horizontal
   * coordinates.
   *
   * Converts the given equatorial coordinates into horizontal coordinates. The
   * results will change over time as the Earth rotates. Therefore, the
   * UpdateLst() function should be called before calling this function.
   *
   * @param ra The right ascension angle in radians.
   * @param dec The declination angle in radians.
   * @return HorizontalCoordinates
   */
  HorizontalCoordinates EquatorialToHorizontal(double ra, double dec);

  /**
   * @brief Updates the local sidereal time.
   *
   * Updates the local sidereal time based on the given Julian date. The Julian
   * date is the number of days since the beginning of the Julian period, which
   * started on January 1, 4713 BC. The Julian date is used in astronomy to
   * avoid the complexities of the Gregorian calendar.
   *
   * @param jd The Julian date.
   */
  void UpdateLst(double jd);
};

#endif  // LIB_ASTROCALCULATOR_ASTROCALCULATOR_H_
