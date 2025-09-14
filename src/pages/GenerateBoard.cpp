// #include <ctime>
#include <cursesw.h>
#include "GenerateBoard.hpp"
#include "../Text.hpp"

GenerateBoard::GenerateBoard() {
  this->board = nullptr;

  this->boardSize = 6;
}

GenerateBoard::~GenerateBoard() {
  if (this->board != nullptr) {
    delete this->board;
    this->board = nullptr;
  }
}

void GenerateBoard::render() {
  clear();

  Text::writeAlignLeft(0, "press ESC to return back to previous menu");

  if (this->board == nullptr) {
    Text::writeAlignLeft(1, "press ENTER to generate a %dx%d board", this->boardSize, this->boardSize);
  } else {
    // TODO: render board
  }
}

int GenerateBoard::onKeyPress(int key) {
  int status = StatusNop;

  switch (key) {
    case 10:
    case KEY_ENTER: {
      if (this->board == nullptr) {
        // uint32_t this->boardSeed = std::time(NULL);
        this->boardSeed = 1690896737;

        this->board = new Board(this->boardSize, this->boardSize);
        this->board->generate(this->boardSeed);
      }
      break;
    }

    case 27: {
      status = StatusPageClosed;
      break;
    }
  }

  return status;
}
