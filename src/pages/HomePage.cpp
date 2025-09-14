#include <cursesw.h>
#include "HomePage.hpp"
#include "GenerateBoardPage.hpp"
#include "../Text.hpp"

HomePage::HomePage() {
  this->selectedMenu = 0;

  this->page = nullptr;
}

HomePage::~HomePage() {
  if (this->page != nullptr) {
    delete this->page;
    this->page = nullptr;
  }
}

void HomePage::render() {
  if (this->page != nullptr) {
    this->page->render();
    return;
  }

  clear();

  Text::writeAlignCenter(LINES / 2 - 5, "Binary Sudoku");

  Text::writeAlignCenter(LINES / 2 - 1, this->selectedMenu == 0 ? "> New game <" : "New game");
  Text::writeAlignCenter(LINES / 2 + 1, this->selectedMenu == 1 ? "> Generate board <" : "Generate board");
  Text::writeAlignCenter(LINES / 2 + 3, this->selectedMenu == 2 ? "> Exit <" : "Exit");

  if (this->selectedMenu == 0) {
    Text::writeAlignLeft(LINES - 1, "Not implemented yet");
  }
}

int HomePage::onKeyPress(int key) {
  if (this->page != nullptr) {
    int pageStatus = this->page->onKeyPress(key);

    if (pageStatus & StatusPageClosed) {
      pageStatus = pageStatus & ~StatusPageClosed;

      delete this->page;
      this->page = nullptr;
    }

    return pageStatus;
  }

  int currentStatus = StatusNop;

  switch(key) {
    case KEY_UP: {
      if (this->selectedMenu > 0) {
        this->selectedMenu = this->selectedMenu - 1;
      } else {
        this->selectedMenu = 2;
      }
      break;
    }

    case KEY_DOWN: {
      if (this->selectedMenu < 2) {
        this->selectedMenu = this->selectedMenu + 1;
      } else {
        this->selectedMenu = 0;
      }
      break;
    }

    // KEY_ENTER refers to the enter key on the numeric keypad, ascii 10 is the main enter key
    // https://stackoverflow.com/a/38214436/1806628
    case 10:
    case KEY_ENTER: {
      switch (this->selectedMenu) {
        case 0: {
          // TODO: implement
          break;
        }

        case 1: {
          this->page = new GenerateBoardPage();
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
