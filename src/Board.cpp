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

  this->tiles->at(0 * this->height + 0) = new Tile(UNDEFINED);
  this->tiles->at(0 * this->height + 1) = new Tile(UNDEFINED);
  this->tiles->at(0 * this->height + 2) = new Tile(UNDEFINED);
  this->tiles->at(0 * this->height + 3) = new Tile(ONE);

  this->tiles->at(1 * this->height + 0) = new Tile(UNDEFINED);
  this->tiles->at(1 * this->height + 1) = new Tile(ONE);
  this->tiles->at(1 * this->height + 2) = new Tile(ONE);
  this->tiles->at(1 * this->height + 3) = new Tile(UNDEFINED);

  this->tiles->at(2 * this->height + 0) = new Tile(ZERO);
  this->tiles->at(2 * this->height + 1) = new Tile(ZERO);
  this->tiles->at(2 * this->height + 2) = new Tile(UNDEFINED);
  this->tiles->at(2 * this->height + 3) = new Tile(ONE);

  this->tiles->at(3 * this->height + 0) = new Tile(UNDEFINED);
  this->tiles->at(3 * this->height + 1) = new Tile(ONE);
  this->tiles->at(3 * this->height + 2) = new Tile(ZERO);
  this->tiles->at(3 * this->height + 3) = new Tile(UNDEFINED);
}

Tile * Board::getTileAt(uint8_t x, uint8_t y) {
  return this->tiles->at(y * this->height + x);
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
