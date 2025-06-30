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

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_search_by_position);
  UNITY_END();
}

void loop() {}
