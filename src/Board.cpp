#include <algorithm>
#include "Board.hpp"
#include "Random.hpp"

Board::Board(uint8_t width, uint8_t height) {
  this->width = std::clamp(width, (uint8_t)2, (uint8_t)16);
  this->height = std::clamp(height, (uint8_t)2, (uint8_t)16);

  this->tiles = new std::vector<Tile *>(this->width * this->height);

  for(uint8_t i = 0; i < this->tiles->size(); i++) {
    this->tiles->at(i) = new Tile(UNDEFINED);
  }
}

void Board::populate(uint32_t seed) {
  if (seed == 0) {
    Random::setSeed();
  } else {
    Random::setSeed(seed);
  }

  uint8_t startX = Random::between(0, this->width);
  uint8_t startY = Random::between(0, this->height);
  TileValues startValue = Random::boolean() ? ONE : ZERO;
  this->setTileAt(startX, startY, startValue, true);

  TileValues neighbourValue = Random::boolean() ? ONE : ZERO;
  bool placedBlock = false;
  do {
    uint8_t direction = Random::between(0, 3);
    switch(direction) {
      case 0:
        placedBlock = this->setTileAt(startX - 1, startY, neighbourValue, true);
        break;
      case 1:
        placedBlock = this->setTileAt(startX, startY + 1, neighbourValue, true);
        break;
      case 2:
        placedBlock = this->setTileAt(startX + 1, startY, neighbourValue, true);
        break;
      case 3:
        placedBlock = this->setTileAt(startX, startY - 1, neighbourValue, true);
        break;
    }
  } while(placedBlock == false);

  this->validate();
}

Tile * Board::getTileAt(uint8_t x, uint8_t y) {
  if (x >= this->width || y >= this->height) {
    return nullptr;
  }

  return this->tiles->at(y * this->height + x);
}

bool Board::setTileAt(uint8_t x, uint8_t y, Tile * tile) {
  if (x >= this->width || y >= this->height) {
    return false;
  }

  this->tiles->at(y * this->height + x) = tile;
  return true;
}

bool Board::setTileAt(uint8_t x, uint8_t y, TileValues value) {
  Tile * tile = this->getTileAt(x, y);

  if (tile == nullptr) {
    return false;
  }

  tile->value = value;
  return true;
}

bool Board::setTileAt(uint8_t x, uint8_t y, TileValues value, bool isLocked) {
  Tile * tile = this->getTileAt(x, y);

  if (tile == nullptr) {
    return false;
  }

  tile->value = value;
  tile->isLocked = isLocked;
  return true;
}

void Board::validate() {
  for(uint8_t y = 0; y < this->height; y++) {
    for(uint8_t x = 0; x < this->width; x++) {
      Tile * tile = this->getTileAt(x, y);

      if (tile->value == UNDEFINED) {
        tile->isIncorrect = false;
        continue;
      }

      tile->isIncorrect =
        this->isInHorizontalTriplet(x, y)
        || this->isInVerticalTriplet(x, y)
        || this->hasTooManySameSymbolsInRow(x, y)
        || this->hasTooManySameSymbolsInColumn(x, y)
      ;
    }
  }
}

bool Board::isInHorizontalTriplet(uint8_t x, uint8_t y) {
  Tile * thisTile = this->getTileAt(x, y);

  Tile * left1 = this->getTileAt(x - 1, y);
  Tile * left2 = this->getTileAt(x - 2, y);
  Tile * right1 = this->getTileAt(x + 1, y);
  Tile * right2 = this->getTileAt(x + 2, y);

  bool isMiddle = thisTile->equals(left1) && thisTile->equals(right1);
  bool isRight = thisTile->equals(left1) && thisTile->equals(left2);
  bool isLeft = thisTile->equals(right1) && thisTile->equals(right2);

  return isMiddle || isRight || isLeft;
}

bool Board::isInVerticalTriplet(uint8_t x, uint8_t y) {
  Tile * thisTile = this->getTileAt(x, y);

  Tile * top1 = this->getTileAt(x, y - 1);
  Tile * top2 = this->getTileAt(x, y - 2);
  Tile * bottom1 = this->getTileAt(x, y + 1);
  Tile * bottom2 = this->getTileAt(x, y + 2);

  bool isMiddle = thisTile->equals(top1) && thisTile->equals(bottom1);
  bool isBottom = thisTile->equals(top1) && thisTile->equals(top2);
  bool isTop = thisTile->equals(bottom1) && thisTile->equals(bottom2);

  return isMiddle || isBottom || isTop;
}

uint8_t Board::countSameSybolsInRow(uint8_t x, uint8_t y) {
  Tile * thisTile = this->getTileAt(x, y);

  if (thisTile == nullptr) {
    return 0;
  }

  uint8_t sum = 0;

  for (uint8_t x = 0; x < this->width; x++) {
    if (thisTile->equals(this->getTileAt(x, y))) {
      sum += 1;
    }
  }

  return sum;
}

uint8_t Board::countSameSybolsInColumn(uint8_t x, uint8_t y) {
  Tile * thisTile = this->getTileAt(x, y);

  if (thisTile == nullptr) {
    return 0;
  }

  uint8_t sum = 0;

  for (uint8_t y = 0; y < this->height; y++) {
    if (thisTile->equals(this->getTileAt(x, y))) {
      sum += 1;
    }
  }

  return sum;
}

bool Board::hasTooManySameSymbolsInRow(uint8_t x, uint8_t y) {
  return this->countSameSybolsInRow(x, y) > (this->width / 2);
}

bool Board::hasTooManySameSymbolsInColumn(uint8_t x, uint8_t y) {
  return this->countSameSybolsInColumn(x, y) > (this->height / 2);
}

uint8_t Board::getWidth() {
  return this->width;
}

uint8_t Board::getHeight() {
  return this->height;
}
