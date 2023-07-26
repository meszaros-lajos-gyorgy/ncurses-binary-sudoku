#include "board.h"

char * board;
int _boardWidth;
int _boardHeight;

void initBoard(int boardWidth, int boardHeight) {
  _boardWidth = boardWidth;
  _boardHeight = boardHeight;
  board = (char *)malloc(boardWidth * boardHeight * sizeof(char));
}

void destroyBoard() {
  free(board);
}

char getTileAt(int x, int y) {
  return board[y * _boardHeight + x];
}

void setTileAt(int x, int y, char value) {
  board[y * _boardHeight + x] = value;
}

bool isTileLockedAt(int x, int y) {
  char tile = getTileAt(x, y);
  return (tile & TileLocked) != 0;
}

bool isTileIncorrectAt(int x, int y) {
  char tile = getTileAt(x, y);
  return (tile & TileError) != 0;
}

bool isTileOneAt(int x, int y) {
  char tile = getTileAt(x, y);
  return (tile & TileValue) != 0;
}

bool isTileDefinedAt(int x, int y) {
  char tile = getTileAt(x, y);
  return (tile & TileDefined) != 0;
}

void populateBoard() {
  board[0 * 4 + 0] = 0;
  board[0 * 4 + 1] = 0;
  board[0 * 4 + 2] = 0;
  board[0 * 4 + 3] = TileDefined | TileLocked | TileValue;

  board[1 * 4 + 0] = 0;
  board[1 * 4 + 1] = TileDefined | TileLocked | TileValue;
  board[1 * 4 + 2] = TileDefined | TileLocked | TileValue;
  board[1 * 4 + 3] = 0;

  board[2 * 4 + 0] = TileDefined | TileLocked;
  board[2 * 4 + 1] = TileDefined | TileLocked;
  board[2 * 4 + 2] = 0;
  board[2 * 4 + 3] = TileDefined | TileLocked | TileValue;

  board[3 * 4 + 0] = 0;
  board[3 * 4 + 1] = TileDefined | TileValue | TileError;
  board[3 * 4 + 2] = TileDefined | TileLocked;
  board[3 * 4 + 3] = 0;
}
