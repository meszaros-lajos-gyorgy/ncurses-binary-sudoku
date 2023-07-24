#include <stdlib.h>
#include <ncurses.h>

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

/**
 * least significant (right most) bit: 0 = undefined, 1 = defined
 * 2nd least significant bit: value of the tile
 * 3rd least significant bit: 0 = tile can be edited, 1 = tile is locked
 * most significant bit: 0 = tile is okay, 1 = tile is incorrect
 */
enum TileAttrs {
  TileDefined   = 0b0001,
  TileValue     = 0b0010,
  TileLocked    = 0b0100,
  TileError     = 0b1000
};

char * board;

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

  board = malloc(boardWidth * boardHeight * sizeof(char));

  board[0 * 4 + 0] = 0;
  board[0 * 4 + 1] = 0;
  board[0 * 4 + 2] = 0;
  board[0 * 4 + 3] = TileLocked | (TileValue & 0b1111);

  board[1 * 4 + 0] = 0;
  board[1 * 4 + 1] = TileLocked | (TileValue & 0b1111);
  board[1 * 4 + 2] = TileLocked | (TileValue & 0b1111);
  board[1 * 4 + 3] = 0;

  board[2 * 4 + 0] = TileLocked | (TileValue & 0b0000);
  board[2 * 4 + 1] = TileLocked | (TileValue & 0b0000);
  board[2 * 4 + 2] = 0;
  board[2 * 4 + 3] = TileLocked | (TileValue & 0b1111);

  board[3 * 4 + 0] = 0;
  board[3 * 4 + 1] = (TileValue & 0b1111) | (TileError & 0b1111);
  board[3 * 4 + 2] = TileLocked | (TileValue & 0b0000);
  board[3 * 4 + 3] = 0;
}

void teardown() {
  free(board);

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

  mvprintw(0, 0, "Press the [arrow keys] to move and press [q] to exit!");
  mvprintw(1, 0, "Press [space] to flip tile!");
  refresh();

  box(boardWindow, 0, 0);

  for(int y = 0; y < boardHeight; y++) {
    for(int x = 0; x < boardWidth; x++) {
      char tile = board[y * boardHeight + x];
      attr_t tileColor = COLOR_PAIR(
        tile & TileError ? ColorError : (
          tile & TileValue ? ColorOne : ColorZero
        )
      );
      wattron(boardWindow, tileColor);
      mvwprintw(boardWindow, y + 1, x * 2 + 1, tile & TileLocked ? "[]" : "  ");
      wattroff(boardWindow, tileColor);
    }
  }

  char tileUnderCursor = board[cursorY * boardHeight + cursorX];
  attr_t cursorColor = COLOR_PAIR(
    tileUnderCursor & TileValue ? ColorCursorOverOne : ColorCursorOverZero
  );
  wattron(boardWindow, cursorColor);
  mvwprintw(boardWindow, cursorY + 1, cursorX * 2 + 1, tileUnderCursor & TileLocked ? "[]" : "  ");
  wattroff(boardWindow, cursorColor);

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
      char tileUnderCursor = board[cursorY * boardHeight + cursorX];
      if (!(tileUnderCursor & TileLocked)) {
        board[cursorY * boardHeight + cursorX] = tileUnderCursor & TileValue ? (TileValue & 0b0000) : (TileValue & 0b1111);
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
