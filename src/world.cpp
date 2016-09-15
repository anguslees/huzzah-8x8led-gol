#include <Arduino.h>

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
