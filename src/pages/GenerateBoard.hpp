#ifndef GENERATE_BOARD_HPP_
#define GENERATE_BOARD_HPP_

#include "Page.hpp"

class GenerateBoard : public Page {
  public:
    GenerateBoard();
    ~GenerateBoard();

    void render();
    int onKeyPress(int key);

  private:
};

#endif
