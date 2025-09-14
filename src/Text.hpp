#ifndef TEXT_HPP_
#define TEXT_HPP_

class Text {
  public:
    static void writeAlignLeft(int y, const char* text, ...);
    static void writeAlignCenter(int y, const char* text, ...);
    static void writeAlignRight(int y, const char* text, ...);
};

#endif
