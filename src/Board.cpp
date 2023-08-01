#include <algorithm>
#include "Board.hpp"
#include "Random.hpp"
#include <cursesw.h>

Board::Board(uint8_t width, uint8_t height) {
  this->width = std::clamp(width, (uint8_t)2, (uint8_t)16);
  this->height = std::clamp(height, (uint8_t)2, (uint8_t)16);

  this->tiles = new std::vector<Tile *>(this->width * this->height);

  for(uint8_t i = 0; i < this->tiles->size(); i++) {
    this->tiles->at(i) = new Tile(UNDEFINED);
  }
}

uint32_t Board::populate(uint32_t seed) {
  Random::setSeed(seed);
  this->seed = seed;

  uint32_t tries = 0;

  do {
    tries++;
    mvprintw(1, 0, "try: %d", tries);
    refresh();

    // create a checkerboard pattern
    for (uint8_t y = 0; y < this->height; y++) {
      for (uint8_t x = 0; x < this->width; x++) {
        if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1)) {
          this->setTileAt(x, y, ONE);
        } else {
          this->setTileAt(x, y, ZERO);
        }
      }
    }

    // swap 2 random tiles 100 times
    for (uint32_t i = 0; i < 100; i++) {
      uint8_t aX = Random::between(0, this->width);
      uint8_t aY = Random::between(0, this->height);
      uint8_t bX = Random::between(0, this->width);
      uint8_t bY = Random::between(0, this->height);
      TileValues tmp = this->getTileAt(aX, aY)->value;
      this->setTileAt(aX, aY, this->getTileAt(bX, bY)-> value);
      this->setTileAt(bX, bY, tmp);
    }

    uint32_t numberOfInvalidTiles = this->validate();

    constexpr uint32_t FAIL_AFTER_N_TRIES = 10000;

    uint32_t remainingTriesForImprovement = FAIL_AFTER_N_TRIES;
    while (!this->isSolved() && remainingTriesForImprovement > 0) {
      uint8_t aX = Random::between(0, this->width);
      uint8_t aY = Random::between(0, this->height);
      uint8_t bX = Random::between(0, this->width);
      uint8_t bY = Random::between(0, this->height);

      TileValues tmp = this->getTileAt(aX, aY)->value;
      this->setTileAt(aX, aY, this->getTileAt(bX, bY)-> value);
      this->setTileAt(bX, bY, tmp);

      uint32_t newNumberOfInvalidTiles = this->validate();

      if (newNumberOfInvalidTiles >= numberOfInvalidTiles) {
      // if the new board is worse then the previous, then undo
        TileValues tmp = this->getTileAt(aX, aY)->value;
        this->setTileAt(aX, aY, this->getTileAt(bX, bY)-> value);
        this->setTileAt(bX, bY, tmp);
        remainingTriesForImprovement--;
      } else {
        // the board is now less "unsolved" by having less invalid tiles
        numberOfInvalidTiles = newNumberOfInvalidTiles;
      }
    }

    this->validate();
  } while(!this->isSolved());

  return tries;
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

bool Board::isTileValid(uint8_t x, uint8_t y) {
  Tile * tile = this->getTileAt(x, y);

  if (tile->value == UNDEFINED) {
    return true;
  }

  if (
    this->isInHorizontalTriplet(x, y)
    || this->isInVerticalTriplet(x, y)
    || this->hasTooManySameSymbolsInRow(x, y)
    || this->hasTooManySameSymbolsInColumn(x, y)
  ) {
    return false;
  }

  return true;
}

uint32_t Board::validate() {
  uint32_t numberOfInvalidTiles = 0;

  for(uint8_t y = 0; y < this->height; y++) {
    for(uint8_t x = 0; x < this->width; x++) {
      Tile * tile = this->getTileAt(x, y);
      tile->isIncorrect = !this->isTileValid(x, y);
      if (tile->isIncorrect) {
        numberOfInvalidTiles++;
      }
    }
  }

  return numberOfInvalidTiles;
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

bool Board::isSolved() {
  for (uint8_t i = 0; i < this->width * this->height; i++) {
    if (this->tiles->at(i)->value == UNDEFINED || this->tiles->at(i)->isIncorrect) {
      return false;
    }
  }

  return true;
}
