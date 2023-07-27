#include <algorithm>
#include "Board.hpp"

Board::Board(uint8_t width, uint8_t height) {
  this->width = std::clamp(width, (uint8_t)2, (uint8_t)16);
  this->height = std::clamp(height, (uint8_t)2, (uint8_t)16);
}

void Board::populate() {
  this->tiles = new std::vector<Tile *>(this->width * this->height);

  for(uint8_t i = 0; i < this->tiles->size(); i++) {
    this->tiles->at(i) = new Tile(UNDEFINED);
  }

  // a simple 8x8 puzzle
  if (this->width == 8 && this->height == 8) {
    this->setTileAt(1, 0, new Tile(ZERO));
    this->setTileAt(2, 0, new Tile(ZERO));
    this->setTileAt(5, 0, new Tile(ONE));

    this->setTileAt(0, 1, new Tile(ONE));
    this->setTileAt(1, 1, new Tile(ZERO));
    this->setTileAt(3, 1, new Tile(ONE));
    this->setTileAt(5, 1, new Tile(ONE));

    this->setTileAt(7, 2, new Tile(ZERO));

    this->setTileAt(1, 3, new Tile(ONE));
    this->setTileAt(6, 3, new Tile(ONE));
    this->setTileAt(7, 3, new Tile(ZERO));

    this->setTileAt(0, 4, new Tile(ZERO));
    this->setTileAt(4, 4, new Tile(ONE));

    this->setTileAt(3, 5, new Tile(ZERO));
    this->setTileAt(7, 5, new Tile(ONE));

    this->setTileAt(1, 6, new Tile(ONE));
    this->setTileAt(4, 6, new Tile(ONE));

    this->setTileAt(7, 7, new Tile(ONE));
  }
}

Tile * Board::getTileAt(uint8_t x, uint8_t y) {
  if (x < 0 || x >= this->width) {
    return nullptr;
  }

  if (y < 0 || y >= this->height) {
    return nullptr;
  }

  return this->tiles->at(y * this->height + x);
}

void Board::setTileAt(uint8_t x, uint8_t y, Tile * value) {
  if (x < 0 || x >= this->width) {
    return;
  }

  if (y < 0 || y >= this->height) {
    return;
  }

  this->tiles->at(y * this->height + x) = value;
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
      ;
    }
  }
}

bool Board::isInHorizontalTriplet(uint8_t x, uint8_t y) {
  Tile * self = this->getTileAt(x, y);

  Tile * left1 = this->getTileAt(x - 1, y);
  Tile * left2 = this->getTileAt(x - 2, y);
  Tile * right1 = this->getTileAt(x + 1, y);
  Tile * right2 = this->getTileAt(x + 2, y);

  bool isMiddle = left1 != nullptr && right1 != nullptr && self->value == left1->value && self->value == right1->value;
  bool isRight = left1 != nullptr && left2 != nullptr && self->value == left1->value && self->value == left2->value;
  bool isLeft = right1 != nullptr && right2 != nullptr && self->value == right1->value && self->value == right2->value;

  return isMiddle || isRight || isLeft;
}

bool Board::isInVerticalTriplet(uint8_t x, uint8_t y) {
  Tile * self = this->getTileAt(x, y);

  Tile * top1 = this->getTileAt(x, y - 1);
  Tile * top2 = this->getTileAt(x, y - 2);
  Tile * bottom1 = this->getTileAt(x, y + 1);
  Tile * bottom2 = this->getTileAt(x, y + 2);

  bool isMiddle = top1 != nullptr && bottom1 != nullptr && self->value == top1->value && self->value == bottom1->value;
  bool isBottom = top1 != nullptr && top2 != nullptr && self->value == top1->value && self->value == top2->value;
  bool isTop = bottom1 != nullptr && bottom2 != nullptr && self->value == bottom1->value && self->value == bottom2->value;

  return isMiddle || isBottom || isTop;
}

uint8_t Board::getWidth() {
  return this->width;
}

uint8_t Board::getHeight() {
  return this->height;
}
