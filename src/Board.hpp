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
    void setTileAt(uint8_t x, uint8_t y, Tile * tile);
    void setTileAt(uint8_t x, uint8_t y, TileValues value);
    void setTileAt(uint8_t x, uint8_t y, TileValues value, bool isLocked);
    void validate();
    uint8_t getWidth();
    uint8_t getHeight();

  private:
    uint8_t width;
    uint8_t height;
    std::vector<Tile *> * tiles;

    bool isInHorizontalTriplet(uint8_t x, uint8_t y);
    bool isInVerticalTriplet(uint8_t x, uint8_t y);
    uint8_t countSameSybolsInRow(uint8_t x, uint8_t y);
    uint8_t countSameSybolsInColumn(uint8_t x, uint8_t y);
    bool hasTooManySameSymbolsInRow(uint8_t x, uint8_t y);
    bool hasTooManySameSymbolsInColumn(uint8_t x, uint8_t y);
};

#endif
