#include <cursesw.h>
#include "Home.hpp"
#include "../Text.hpp"

Home::Home() {}
Home::~Home() {}

void Home::render() {
  clear();

  Text::writeAlignCenter(COLS / 2, LINES / 2, "Binary Sudoku");

  Text::writeAlignRight(COLS, LINES - 1, "press [q] to quit");
}

int Home::onKeyPress(int key) {
  int status = StatusNop;

  switch(key) {
    case 'q': {
      status = (StatusKeyHandled | StatusPageClosed);
    }
  }

  return status;
}
