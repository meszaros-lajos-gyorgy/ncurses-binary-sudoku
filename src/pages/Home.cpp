#include <cursesw.h>
#include "Home.hpp"
#include "GenerateBoard.hpp"
#include "../Text.hpp"

Home::Home() {
  selectedMenu = 0;

  page = nullptr;
}

Home::~Home() {
  if (page != nullptr) {
    delete page;
    page = nullptr;
  }
}

void Home::render() {
  if (page != nullptr) {
    page->render();
    return;
  }

  clear();

  Text::writeAlignCenter(COLS / 2, LINES / 2 - 5, "Binary Sudoku");

  Text::writeAlignCenter(COLS / 2, LINES / 2 - 1, selectedMenu == 0 ? "> New game <" : "New game");
  Text::writeAlignCenter(COLS / 2, LINES / 2 + 1, selectedMenu == 1 ? "> Generate board <" : "Generate board");
  Text::writeAlignCenter(COLS / 2, LINES / 2 + 3, selectedMenu == 2 ? "> Exit <" : "Exit");

  if (selectedMenu == 0) {
    Text::writeAlignLeft(0, LINES - 1, "Not implemented yet");
  }
}

int Home::onKeyPress(int key) {
  if (page != nullptr) {
    int pageStatus = page->onKeyPress(key);

    if (pageStatus & StatusPageClosed) {
      pageStatus = pageStatus & ~StatusPageClosed;

      delete page;
      page = nullptr;
    }

    return pageStatus;
  }

  int currentStatus = StatusNop;

  switch(key) {
    case KEY_UP: {
      if (selectedMenu > 0) {
        selectedMenu = selectedMenu - 1;
      } else {
        selectedMenu = 2;
      }
      break;
    }

    case KEY_DOWN: {
      if (selectedMenu < 2) {
        selectedMenu = selectedMenu + 1;
      } else {
        selectedMenu = 0;
      }
      break;
    }

    // KEY_ENTER refers to the enter key on the numeric keypad, ascii 10 is the main enter key
    // https://stackoverflow.com/a/38214436/1806628
    case 10:
    case KEY_ENTER: {
      switch (selectedMenu) {
        case 0: {
          // TODO: implement
          break;
        }

        case 1: {
          page = new GenerateBoard();
          break;
        }

        case 2: {
          currentStatus = StatusPageClosed;
          break;
        }
      }
      break;
    }
  }

  return currentStatus;
}
