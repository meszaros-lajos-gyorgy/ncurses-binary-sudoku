#include <cursesw.h>
#include "GenerateBoard.hpp"
#include "../Text.hpp"

// TODO: inputs from user:
//   - board size (width × height)
//   - seed

GenerateBoard::GenerateBoard() {}

GenerateBoard::~GenerateBoard() {}

void GenerateBoard::render() {
  clear();

  Text::writeAlignLeft(0, 0, "TODO: implement generate board page");
  Text::writeAlignLeft(0, 1, "press ESC to return back to previous menu");
}

int GenerateBoard::onKeyPress(int key) {
  int status = StatusNop;

  switch (key) {
    case 27: {
      status = StatusPageClosed;
      break;
    }
  }

  return status;
}
