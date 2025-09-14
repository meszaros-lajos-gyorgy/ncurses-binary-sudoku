#ifndef PAGE_HPP_
#define PAGE_HPP_

enum Statuses {
  StatusNop = 0,
  StatusPageClosed = 1 << 0
};

class Page {
  public:
    virtual ~Page();

    virtual void render();
    virtual int onKeyPress(int key) = 0;
};

#endif
