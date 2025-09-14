#ifndef GENERATE_BOARD_HPP_
#define GENERATE_BOARD_HPP_

#include <cstdint>
#include "Page.hpp"
#include "../board/Board.hpp"

class GenerateBoard : public Page {
  public:
    GenerateBoard();
    ~GenerateBoard();

    void render();
    int onKeyPress(int key);

  private:
    uint32_t boardSeed;
    uint8_t boardSize;
    Board * board;
};

#endif
