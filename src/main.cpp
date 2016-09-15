#ifndef UNIT_TEST

#ifdef ARDUINO

#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

#include "world.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

World worlds[2];
uint8_t current_world;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up");

  randomSeed(os_random());

  matrix.begin(0x70);  // pass in the address

  current_world = 0;
  worlds[current_world].randomise();
}

void loop() {
  const World& old_world = worlds[current_world];
  current_world = (current_world + 1) % 2;
  World& new_world = worlds[current_world];

  matrix.clear();
  bool any_changes = false;

  for (uint8_t x = 0; x < XSIZE; ++x) {
    for (uint8_t y = 0; y < YSIZE; ++y) {
      auto old_live = old_world.is_live(x, y);
      auto n = old_world.live_neighbours(x, y);

      bool live = old_live ? (n == 2 || n == 3) : (n == 3);

      if (!any_changes) {
	any_changes = (live != old_live);
      }

      new_world.set_live(x, y, live);
      matrix.drawPixel(x, y, live ? LED_GREEN : 0);
    }
  }

  matrix.writeDisplay();
  delay(500);

  if (!any_changes) {
    delay(3000);
    new_world.randomise();
  }
}

#else /* !ARDUINO */

int main(int argc, char **argv) {
  return 0;
}

#endif
#endif
