#include "Random.hpp"

void Random::setSeed() {
  Random::setSeed(std::time(NULL));
}

void Random::setSeed(uint32_t seed) {
  std::srand(seed);
}

double Random::between0And1() {
  return static_cast<double>(std::rand()) / RAND_MAX;
}

uint8_t Random::between(uint8_t min, uint8_t max) {
  return min + Random::between0And1() * (max - min);
}

bool Random::boolean() {
  return Random::between0And1() > 0.5;
}
