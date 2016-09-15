#ifdef ARDUINO
#include <Arduino.h>
#else

#include <stdlib.h>
static uint random(uint max) {
  return rand() % max;
}

#endif

#include "world.h"

uint8_t World::live_neighbours(uint8_t x, uint8_t y) const {
  return (is_live(x-1, y-1) +
	  is_live(x-1, y) +
	  is_live(x-1, y+1) +
	  is_live(x, y-1) +
	  is_live(x, y+1) +
	  is_live(x+1, y-1) +
	  is_live(x+1, y) +
	  is_live(x+1, y+1));
}

void World::randomise() {
  for (uint8_t x = 0; x < XSIZE; ++x)
    for (uint8_t y = 0; y < YSIZE; ++y) {
      bool state = random(2);
      set_live(x, y, state);
    }
}
