#include <ncurses.h>
#include "board.h"

#define CURSOR_OFF 0

WINDOW * boardWindow;
int lastPressedKey = 0;
bool programCanExit = false;

const int boardWidth = 4;
const int boardHeight = 4;

int cursorX = 0;
int cursorY = 0;

enum Colors {
  ColorCursorOverZero = 1,
  ColorCursorOverOne,
  ColorZero,
  ColorOne,
  ColorError
};

void setup() {
  initscr();

  cbreak();
  noecho();
  curs_set(CURSOR_OFF);

  keypad(stdscr, true);
  start_color();

  init_pair(ColorCursorOverZero, COLOR_WHITE, COLOR_BLUE);
  init_pair(ColorCursorOverOne, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(ColorZero, COLOR_WHITE, COLOR_BLACK);
  init_pair(ColorOne, COLOR_BLACK, COLOR_WHITE);
  init_pair(ColorError, COLOR_BLACK, COLOR_RED);

  initBoard(boardWidth, boardHeight);
  populateBoard();

  mvprintw(0, 0, "Press the [arrow keys] to move and press [q] to exit!");
  mvprintw(1, 0, "Press [space] to flip tile!");
  refresh();
}

void teardown() {
  destroyBoard();

  keypad(stdscr, false);

  endwin();
}

void view() {
  int windowPositionTop = 4;
  int windowPositionLeft = 4;

  if (boardWindow == NULL) {
    boardWindow = newwin(
      boardHeight + 2,
      boardWidth * 2 + 2,
      windowPositionTop,
      windowPositionLeft
    );
  }

  box(boardWindow, 0, 0);

  for(int y = 0; y < boardHeight; y++) {
    for(int x = 0; x < boardWidth; x++) {
      attr_t color;

      if (x == cursorX && y == cursorY) {
        color = COLOR_PAIR(isTileOneAt(x, y) ? ColorCursorOverOne : ColorCursorOverZero);
      } else {
        if (isTileIncorrectAt(x, y)) {
          color = COLOR_PAIR(ColorError);
        } else {
          color = COLOR_PAIR(isTileOneAt(x, y) ? ColorOne : ColorZero);
        }
      }

      wattron(boardWindow, color);
      mvwprintw(boardWindow, y + 1, x * 2 + 1, isTileLockedAt(x, y) ? "[]" : "  ");
      wattroff(boardWindow, color);
    }
  }

  wrefresh(boardWindow);
}

void controller() {
  switch(lastPressedKey) {
    case KEY_LEFT:
      if (cursorX > 0) {
        cursorX -= 1;
      }
      break;
    case KEY_RIGHT:
      if (cursorX < boardWidth - 1) {
        cursorX += 1;
      }
      break;
    case KEY_UP:
      if (cursorY > 0) {
        cursorY -= 1;
      }
      break;
    case KEY_DOWN:
      if (cursorY < boardHeight - 1) {
        cursorY += 1;
      }
      break;
    case ' ':
      if (!isTileLockedAt(cursorX, cursorY)) {
        setTileAt(cursorX, cursorY, isTileOneAt(cursorX, cursorY) ? (TileValue & 0b0000) : (TileValue & 0b1111));
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
