#ifndef TILE_HPP_
#define TILE_HPP_

#include <wchar.h>

class Tile {
  public:
    bool isDefined;
    bool isLocked;
    bool isIncorrect;
    bool value;

    Tile(bool isDefined, bool value, bool isLocked, bool isIncorrect = false);

    wchar_t * render();
};

#endif
