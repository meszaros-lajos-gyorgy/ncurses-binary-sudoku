#ifndef HOME_PAGE_HPP_
#define HOME_PAGE_HPP_

#include <cstdint>
#include "Page.hpp"

class HomePage : public Page {
  public:
    HomePage();
    ~HomePage();

    void render();
    int onKeyPress(int key);
  
  private:
    uint8_t selectedMenu;
    Page * page;
};

#endif
