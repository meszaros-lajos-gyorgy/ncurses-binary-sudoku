#ifndef BOARD_H_
#define BOARD_H_

#include <stdlib.h> // malloc, free
#include <stdbool.h> // bool

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

void initBoard(int boardWidth, int boardHeight);
void destroyBoard();
void populateBoard();

char getTileAt(int x, int y);
void setTileAt(int x, int y, char value);

bool isTileLockedAt(int x, int y);
bool isTileIncorrectAt(int x, int y);
bool isTileOneAt(int x, int y);

#endif
