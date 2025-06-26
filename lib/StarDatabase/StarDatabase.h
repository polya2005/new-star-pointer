/**
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_STARDATABASE_STARDATABASE_H_
#define LIB_STARDATABASE_STARDATABASE_H_

#include <stdint.h>

struct StarDatabaseEntry {
  uint8_t n_names;  // Number of names (up to 5)
  char names[5]
            [23];  // Names of the star, up to 5 names, each up to 22 characters
  char constellation[20];  // Constellation name, up to 19 characters
  double ra;  // Right Ascension in radians
  double dec;  // Declination in radians
  float mag;  // Magnitude of the star
  char spectral_type[18];
  float b_v;  // B-V color index
};

#endif  // LIB_STARDATABASE_STARDATABASE_H_
