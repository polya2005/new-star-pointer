/**
 * Copyright (c) 2025, Boonyakorn Thanpanit
 */

#include <Arduino.h>
#include <StarDatabase.h>
#include <unity.h>

static StarDatabase& star_database = StarDatabase::GetInstance();

void setUp(void) { star_database.Init(); }

void test_test(void) { TEST_ASSERT_TRUE(true); }

void test_root(void) {
  TEST_ASSERT_EQUAL(6170, star_database.GetBallTreeRoot());
}

void test_search_by_position(void) {
  double ra = 1.373;
  double dec = -0.14292;
  int16_t index = star_database.SearchByPosition(ra, dec);
  TEST_ASSERT_EQUAL(705, index);
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_test);
  RUN_TEST(test_root);
  RUN_TEST(test_search_by_position);
  UNITY_END();
}

void loop() {}
