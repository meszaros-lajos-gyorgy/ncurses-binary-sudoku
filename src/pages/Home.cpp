#include <cursesw.h>
#include "Home.hpp"
#include "../Text.hpp"

Home::Home() {
  selectedMenu = 0;
}

Home::~Home() {}

void Home::render() {
  clear();

  Text::writeAlignCenter(COLS / 2, LINES / 2 - 5, "Binary Sudoku");

  Text::writeAlignCenter(COLS / 2, LINES / 2 - 1, selectedMenu == 0 ? "> New game <" : "New game");
  Text::writeAlignCenter(COLS / 2, LINES / 2 + 1, selectedMenu == 1 ? "> Generate board <" : "Generate board");
  Text::writeAlignCenter(COLS / 2, LINES / 2 + 3, selectedMenu == 2 ? "> Exit <" : "Exit");

  if (selectedMenu == 0 || selectedMenu == 1) {
    Text::writeAlignLeft(0, LINES - 1, "Not implemented yet");
  }
}

int Home::onKeyPress(int key) {
  int status = StatusNop;

  switch(key) {
    case KEY_UP: {
      if (selectedMenu > 0) {
        selectedMenu = selectedMenu - 1;
      } else {
        selectedMenu = 2;
      }

      status = StatusKeyHandled;
      break;
    }

    case KEY_DOWN: {
      if (selectedMenu < 2) {
        selectedMenu = selectedMenu + 1;
      } else {
        selectedMenu = 0;
      }

      status = StatusKeyHandled;
      break;
    }

    // KEY_ENTER refers to the enter key on the numeric keypad (see https://stackoverflow.com/a/38214436/1806628)
    case 10:
    case KEY_ENTER: {
      switch (selectedMenu) {
        case 0: {
          status = StatusKeyHandled;
          break;
        }

        case 1: {
          status = StatusKeyHandled;
          break;
        }

        case 2: {
          status = (StatusKeyHandled | StatusPageClosed);
          break;
        }
      }
      break;
    }
  }

  return status;
}
