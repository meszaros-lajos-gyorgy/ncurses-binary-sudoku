#include <cstring>
#include <cursesw.h>
#include "Text.hpp"

void Text::writeAlignLeft(int x, int y, std::string text) {
  mvprintw(y, x, "%s", text.c_str());
}

void Text::writeAlignCenter(int x, int y, std::string text) {
  mvprintw(y, x - text.length() / 2, "%s", text.c_str());
}

void Text::writeAlignRight(int x, int y, std::string text) {
  mvprintw(y, x - text.length(), "%s", text.c_str());
}
