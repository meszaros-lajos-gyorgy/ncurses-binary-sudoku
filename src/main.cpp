#include <iostream>
#include <locale>
#include <cursesw.h>
#include <wchar.h>

#include "Board.hpp"

#define CURSOR_OFF 0

WINDOW * boardWindow;
int lastPressedKey = 0;
bool programCanExit = false;

Board * board;

int cursorX = 0;
int cursorY = 0;

enum Colors {
  ColorDefault = 1,
  ColorCursor,
  ColorError,
  ColorSolved
};

void setup() {
  setlocale(LC_ALL, "");

  initscr();

  cbreak();
  noecho();
  curs_set(CURSOR_OFF);

  keypad(stdscr, true);
  start_color();

  init_pair(ColorDefault, COLOR_WHITE, COLOR_BLACK);
  init_pair(ColorCursor, COLOR_BLACK, COLOR_YELLOW);
  init_pair(ColorError, COLOR_RED, COLOR_BLACK);
  init_pair(ColorSolved, COLOR_GREEN, COLOR_BLACK);

  board = new Board(8, 8);
  board->populate();

  mvprintw(0, 0, "Press the [arrow keys] to move and press [q] to exit!");
  mvprintw(1, 0, "Press [space] to flip, [0]/[1] to set and [backspace] to clear a tile!");
  refresh();
}

void teardown() {
  board = nullptr;
  keypad(stdscr, false);
  endwin();
}

void view() {
  int windowPositionTop = 4;
  int windowPositionLeft = 4;

  if (boardWindow == NULL) {
    boardWindow = newwin(board->getHeight() + 2, board->getWidth() * 2 + 2, windowPositionTop, windowPositionLeft);
  }

  box(boardWindow, 0, 0);

  for(int y = 0; y < board->getHeight(); y++) {
    for(int x = 0; x < board->getWidth(); x++) {
      Tile * tile = board->getTileAt(x, y);
      attr_t color;

      if (x == cursorX && y == cursorY) {
        color = COLOR_PAIR(ColorCursor);
      } else if (tile->isIncorrect) {
        color = COLOR_PAIR(ColorError);
      } else {
        color = COLOR_PAIR(ColorDefault);
      }

      wmove(boardWindow, y + 1, x * 2 + 1);
      wattron(boardWindow, color);
      waddwstr(boardWindow, tile->render());
      wattroff(boardWindow, color);
    }
  }

  wrefresh(boardWindow);
}

void controller() {
  Tile * tile = board->getTileAt(cursorX, cursorY);

  switch(lastPressedKey) {
    case KEY_LEFT:
      if (cursorX > 0) {
        cursorX -= 1;
      }
      break;
    case KEY_RIGHT:
      if (cursorX < board->getWidth() - 1) {
        cursorX += 1;
      }
      break;
    case KEY_UP:
      if (cursorY > 0) {
        cursorY -= 1;
      }
      break;
    case KEY_DOWN:
      if (cursorY < board->getHeight() - 1) {
        cursorY += 1;
      }
      break;
    case '0':
      if (!tile->isLocked) {
        tile->value = ZERO;
        board->validate();
      }
      break;
    case '1':
      if (!tile->isLocked) {
        tile->value = ONE;
        board->validate();
      }
      break;
    case KEY_BACKSPACE:
      if (!tile->isLocked) {
        tile->value = UNDEFINED;
        board->validate();
      }
      break;
    case ' ':
      if (!tile->isLocked) {
        tile->toggleNext();
        board->validate();
      }
      break;
    case 'q':
      programCanExit = true;
      break;
  }
}

int main() {
  setup();

  do {
    view();
    lastPressedKey = wgetch(stdscr);
    controller();
  } while(!programCanExit);

  teardown();

  return 0;
}
