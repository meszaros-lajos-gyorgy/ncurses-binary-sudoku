#include <cstdlib>
#include "App.hpp"

int main() {
  App * app = new App();

  app->run();

  delete app;
  app = nullptr;

  return EXIT_SUCCESS;
}
