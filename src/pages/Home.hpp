#ifndef HOME_HPP_
#define HOME_HPP_

#include "Page.hpp"

class Home : public Page {
  public:
    Home();
    ~Home();

    void render();
    int onKeyPress(int key);
};

#endif
