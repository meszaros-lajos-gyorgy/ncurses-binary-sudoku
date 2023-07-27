#ifndef TILE_HPP_
#define TILE_HPP_

#include <wchar.h>
#include <cstdint>

enum TileValues {
  UNDEFINED,
  ZERO,
  ONE
};

class Tile {
  public:
    static constexpr uint8_t width = 2;
    static constexpr uint8_t height = 1;

    TileValues value;
    bool isLocked;
    bool isIncorrect;

    Tile(TileValues value);

    wchar_t * render();
    void toggleNext();
};

#endif
