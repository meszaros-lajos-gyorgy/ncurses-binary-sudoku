#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <cstdint>

class Board {
  public:
    Board(uint8_t width, uint8_t height);
    ~Board();

    void generate(uint32_t seed);

  private:
    uint32_t seed;
    uint8_t width;
    uint8_t height;
};

#endif
