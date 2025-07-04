/**
 * Copyright (c) 2025, Boonyakorn Thanpanit
 */

#include <Arduino.h>
#include <StarDatabase.h>
#include <unity.h>

static StarDatabase& star_database = StarDatabase::GetInstance();

void setUp(void) { star_database.Init(); }

void test_search_by_position(void) {
  double ra = 1.373;
  double dec = -0.14292;
  int16_t index = star_database.SearchByPosition(ra, dec);
  TEST_ASSERT_EQUAL(705, index);
}

void test_read_star_entry(void) {
  const int16_t index = 705;  // Example index; corresponds to Rigel
  StarDatabaseEntry entry = star_database.ReadStarEntry(index);
  TEST_ASSERT_EQUAL_UINT8(0, entry.is_invalid);  // 0 means valid
  TEST_ASSERT_EQUAL_STRING("Rigel", entry.name);
  TEST_ASSERT_EQUAL_STRING("β Orionis, β Ori, 19 Orionis, 19 Ori",
                           entry.other_names);
  TEST_ASSERT_EQUAL_FLOAT(1.3724323851005242, entry.ra);
  TEST_ASSERT_EQUAL_FLOAT(-0.14314608748440158, entry.dec);
  TEST_ASSERT_EQUAL_FLOAT(0.12, entry.mag);
  TEST_ASSERT_EQUAL_STRING("B8Ia:", entry.spectral_type);
  TEST_ASSERT_EQUAL_FLOAT(-0.03, entry.b_v);
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_search_by_position);
  RUN_TEST(test_read_star_entry);
  UNITY_END();
}

void loop() {}
