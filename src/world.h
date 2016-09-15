#include <stdint.h>

const uint8_t XSIZE = 8;
const uint8_t YSIZE = 8;

static uint8_t absmod(int8_t i, int8_t n) {
  // It's always annoyed me that % returned negatives...
  return (n + (i % n)) % n;
}

class World {
 public:
  void randomise();
  uint8_t live_neighbours(uint8_t x, uint8_t y) const;
  void set_live(uint8_t x, uint8_t y, bool live) {
    world[x][y] = live;
  }
  bool is_live(int8_t x, int8_t y) const {
    return world[absmod(x, XSIZE)][absmod(y, YSIZE)];
  }

 private:
  bool world[XSIZE][YSIZE];
};
