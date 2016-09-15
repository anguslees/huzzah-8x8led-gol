#ifdef ARDUINO
#include <Arduino.h>
#include <Wire.h>
#else
#include <stdint.h>
#endif

#include <unity.h>

#include "world.h"

#ifdef UNIT_TEST

void test_world() {
  World w;
  for (uint8_t x = 0; x < XSIZE; ++x)
    for (uint8_t y = 0; y < YSIZE; ++y)
      w.set_live(x, y, false);

  for (uint8_t x = 0; x < XSIZE; ++x)
    for (uint8_t y = 0; y < YSIZE; ++y)
      TEST_ASSERT_FALSE(w.is_live(x, y));

  w.set_live(0, 0, true);
  w.set_live(0, 1, true);
  w.set_live(2, 0, true);

  TEST_ASSERT_TRUE(w.is_live(0, 0));
  TEST_ASSERT_TRUE(w.is_live(0, 1));
  TEST_ASSERT_TRUE(w.is_live(2, 0));
  TEST_ASSERT_FALSE(w.is_live(4, 4));
  TEST_ASSERT_FALSE(w.is_live(1, 0));
  TEST_ASSERT_TRUE(w.is_live(0, -7));
  TEST_ASSERT_TRUE(w.is_live(-6, 0));
  TEST_ASSERT_FALSE(w.is_live(-6, -6));

  TEST_ASSERT_EQUAL_UINT8(0, w.live_neighbours(4, 4));
  TEST_ASSERT_EQUAL_UINT8(3, w.live_neighbours(1, 1));
  TEST_ASSERT_EQUAL_UINT8(1, w.live_neighbours(0, 0));
  TEST_ASSERT_EQUAL_UINT8(2, w.live_neighbours(7, 1));
  TEST_ASSERT_EQUAL_UINT8(2, w.live_neighbours(1, 7));
  TEST_ASSERT_EQUAL_UINT8(1, w.live_neighbours(7, 7));
}

void test_randomise() {
  World w;
  w.randomise();

  int count = 0;
  for (uint8_t x = 0; x < XSIZE; ++x)
    for (uint8_t y = 0; y < YSIZE; ++y)
      if (w.is_live(x, y))
	++count;

  // Statistically this should pass "most" of the time
  TEST_ASSERT_INT_WITHIN(10, (XSIZE*YSIZE)/2, count);
}

static void run_tests() {
  UNITY_BEGIN();

  RUN_TEST(test_world);
  RUN_TEST(test_randomise);

  UNITY_END();
}

#ifdef ARDUINO

void setup() {
  randomSeed(os_random());
  run_tests();
}

void loop() {
  delay(500);
}

#else

int main(int argc, char **argv) {
  run_tests();
  return 0;
}

#endif

#endif
