/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_ASTROCALCULATOR_ASTROCALCULATOR_H_
#define LIB_ASTROCALCULATOR_ASTROCALCULATOR_H_

typedef struct {
  float azimuth;  // in radians
  float altitude;  // in radians
} HorizontalCoordinates;

typedef struct {
  float ra;  // in radians
  float dec;  // in radians
} EquatorialCoordinates;

class AstroCalculator {
 private:
  float sin_latitude_, cos_latitude_, longitude_;
  float lst_;  // in radians

  AstroCalculator() {}
  AstroCalculator(const AstroCalculator& other) = delete;
  void operator=(const AstroCalculator& other) = delete;

 public:
  // Returns the instance of the AstroCalculator class
  static AstroCalculator& GetInstance();

  // Sets the observer location to (latitude, longitude) radians
  void SetObserverLocation(float latitude, float longitude);

  // Converts the given horizontal coordinates into equatorial coordinates.
  // The arguments are all in radians.
  EquatorialCoordinates HorizontalToEquatorial(float azimuth, float altitude);

  // Converts the given equatorial coordinates into horizontal coordinates.
  // The arguments are all in radians.
  HorizontalCoordinates EquatorialToHorizontal(float ra, float dec);
};

#endif  // LIB_ASTROCALCULATOR_ASTROCALCULATOR_H_
