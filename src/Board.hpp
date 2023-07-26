#ifndef BOARD_H_
#define BOARD_H_

#include <cstdint>
#include <vector>
#include "Tile.hpp"

class Board {
  public:
    Board(uint8_t width, uint8_t height);

    void populate();
    Tile * getTileAt(uint8_t x, uint8_t y);
    void validate();
    uint8_t getWidth();
    uint8_t getHeight();

  private:
    uint8_t width;
    uint8_t height;
    std::vector<Tile *> * tiles;
};

#endif
