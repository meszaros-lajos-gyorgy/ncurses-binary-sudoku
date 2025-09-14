#ifndef APP_HPP_
#define APP_HPP_

#include "pages/Page.hpp"

class App {
  public:
    App();
    ~App();

    void run();

  private:
    Page * page;
};

#endif
