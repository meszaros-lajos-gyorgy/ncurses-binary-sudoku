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
}

App::~App() {
  keypad(stdscr, false);
  endwin();
}

void App::run() {
  bool programCanExit = false;

  Page * page = new Home();

  int lastStatus = StatusNop;

  do {
    page->render();

    int lastPressedKey = wgetch(stdscr);
    lastStatus = page->onKeyPress(lastPressedKey);

    while (!(lastStatus & StatusKeyHandled)) {
      // TODO: some other parts of the code might want to handle the keypress
      mvprintw(5, 0, "lastPressedKey = %c  ", lastPressedKey);
      lastStatus = lastStatus | StatusKeyHandled;
    }

    if (lastStatus & StatusPageClosed) {
      lastStatus = lastStatus & ~StatusPageClosed;
      programCanExit = true;
    }
  } while(!programCanExit);

  delete page;
  page = nullptr;
}
