#ifndef GENERATE_BOARD_PAGE_HPP_
#define GENERATE_BOARD_PAGE_HPP_

#include <cstdint>
#include "Page.hpp"
#include "../board/Board.hpp"

class GenerateBoardPage : public Page {
  public:
    GenerateBoardPage();
    ~GenerateBoardPage();

    void render();
    int onKeyPress(int key);

  private:
    uint32_t boardSeed;
    uint8_t boardSize;
    Board * board;
};

#endif
