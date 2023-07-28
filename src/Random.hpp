#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <cstdlib>
#include <ctime>
#include <cstdint>

class Random {
  public:
    static void setSeed();
    static void setSeed(uint32_t seed);

    static double between0And1();
    static uint8_t between(uint8_t min, uint8_t max);
    static bool boolean();
};

#endif
