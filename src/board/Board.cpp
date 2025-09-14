#include "Board.hpp"

Board::Board(uint8_t width, uint8_t height) {
  this->width = width;
  this->height = height;
}

Board::~Board() {}

void Board::generate(uint32_t seed) {
  this->seed = seed;
}
