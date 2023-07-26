#include "Tile.hpp"

Tile::Tile(bool isDefined, bool value, bool isLocked, bool isIncorrect) {
  this->isDefined = isDefined;
  this->value = value;
  this->isLocked = isLocked;
  this->isIncorrect = isIncorrect;
}

wchar_t * Tile::render() {
  if (!this->isDefined) {
    return new wchar_t[3] { L' ', L' ', L'\0' };
  }

  if (this->value) {
    return new wchar_t[3] { L'▓', L'▓', L'\0' };
  } else {
    return new wchar_t[3] { L'░', L'░', L'\0' };
  }
}
