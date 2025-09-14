#include <cursesw.h>
#include "App.hpp"
#include "pages/Page.hpp"
#include "pages/Home.hpp"

#define CURSOR_OFF 0

App::App() {
  setlocale(LC_ALL, "");

  initscr();

  cbreak();
  noecho();
  curs_set(CURSOR_OFF);

  keypad(stdscr, true);
  start_color();

  // make sure escape doesn't have to be pressed twice
  // https://stackoverflow.com/a/71567651/1806628
  ESCDELAY = 10;

  this->page = new Home();
}

App::~App() {
  keypad(stdscr, false);
  endwin();

  if (this->page != nullptr) {
    delete this->page;
    this->page = nullptr;
  }
}

void App::run() {
  bool programCanExit = false;

  do {
    this->page->render();

    int lastPressedKey = wgetch(stdscr);
    int pageStatus = this->page->onKeyPress(lastPressedKey);

    if (pageStatus & StatusPageClosed) {
      pageStatus = pageStatus & ~StatusPageClosed;

      delete this->page;
      this->page = nullptr;

      programCanExit = true;
    }
  } while(!programCanExit);
}
