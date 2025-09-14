#include <cstring>
#include <cursesw.h>
#include "Text.hpp"

void Text::writeAlignLeft(int y, const char* text, ...) {
  va_list args;

  char buffer[100];

  va_start(args, text);
  vsprintf(buffer, text, args);
  va_end(args);

  mvprintw(y, 0, "%s", buffer);
}

void Text::writeAlignCenter(int y, const char* text, ...) {
  va_list args;

  va_start(args, text);
  int bufferSize = vsnprintf(NULL, 0, text, args);
  va_end(args);

  char buffer[100];

  va_start(args, text);
  vsprintf(buffer, text, args);
  va_end(args);

  mvprintw(y, COLS / 2 - bufferSize / 2, "%s", buffer);
}

void Text::writeAlignRight(int y, const char* text, ...) {
  va_list args;

  va_start(args, text);
  int bufferSize = vsnprintf(NULL, 0, text, args);
  va_end(args);

  char buffer[100];

  va_start(args, text);
  vsprintf(buffer, text, args);
  va_end(args);

  mvprintw(y, COLS - bufferSize, "%s", buffer);
}
