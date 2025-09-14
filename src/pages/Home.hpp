#ifndef HOME_HPP_
#define HOME_HPP_

#include <cstdio>
#include "Page.hpp"

class Home : public Page {
  public:
    Home();
    ~Home();

    void render();
    int onKeyPress(int key);
  
  private:
    uint8_t selectedMenu;
    Page * page;
};

#endif
