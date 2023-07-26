#include "Board.hpp"

Board::Board(uint8_t width, uint8_t height) {
  this->width = width;
  this->height = height;
}

void Board::populate() {
  this->tiles = new std::vector<Tile *>(this->width * this->height);

  for(int i = 0; i < this->tiles->size(); i++) {
    this->tiles->at(i) = new Tile(UNDEFINED);
  }

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

Tile * Board::getTileAt(uint8_t x, uint8_t y) {
  return this->tiles->at(y * this->height + x);
}

void Board::setTileAt(uint8_t x, uint8_t y, Tile * value) {
  this->tiles->at(y * this->height + x) = value;
}

void Board::validate() {
  for(uint8_t y = 0; y < this->height; y++) {
    for(uint8_t x = 0; x < this->width; x++) {
      Tile * tile = this->getTileAt(x, y);
      tile->isIncorrect = false;
    }
  }
}

uint8_t Board::getWidth() {
  return this->width;
}

uint8_t Board::getHeight() {
  return this->height;
}
