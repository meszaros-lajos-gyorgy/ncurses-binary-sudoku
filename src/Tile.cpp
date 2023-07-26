#include "Tile.hpp"

Tile::Tile(TileValues value) {
  this->value = value;
  this->isLocked = value != UNDEFINED;
  this->isIncorrect = false;
}

wchar_t * Tile::render() {
  wchar_t * chars;

  switch(this->value) {
    case UNDEFINED:
      chars = new wchar_t[3] { L' ', L' ', L'\0' };
      break;
    case ONE:
      chars = new wchar_t[3] { L'▓', L'▓', L'\0' };
      break;
    case ZERO:
      chars = new wchar_t[3] { L'░', L'░', L'\0' };
      break;
  }

  return chars;
}
