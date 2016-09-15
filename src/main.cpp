#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

const uint8_t XSIZE = 8;
const uint8_t YSIZE = 8;

class World {
public:
  uint live_neighbours(uint8_t x, uint8_t y) const;
  void set_live(uint8_t x, uint8_t y, bool live) {
    world[x][y] = live;
  }
  bool is_live(int8_t x, int8_t y) const {
    return world[x % XSIZE][y % YSIZE];
  }
private:
  bool world[XSIZE][YSIZE];
};

uint World::live_neighbours(uint8_t x, uint8_t y) const {
  return (is_live(x-1, y-1) +
	  is_live(x-1, y) +
	  is_live(x-1, y+1) +
	  is_live(x, y-1) +
	  is_live(x, y+1) +
	  is_live(x+1, y-1) +
	  is_live(x+1, y) +
	  is_live(x+1, y+1));
}

static World worlds[2];
static uint8_t current_world;

static void randomise_world(World& world) {
  for (uint8_t x = 0; x < XSIZE; ++x)
    for (uint8_t y = 0; y < YSIZE; ++y) {
      bool state = random(2);
      world.set_live(x, y, state);
    }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up");

  randomSeed(os_random());

  matrix.begin(0x70);  // pass in the address

  current_world = 0;
  randomise_world(worlds[current_world]);
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
    randomise_world(new_world);
  }
}
