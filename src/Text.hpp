#ifndef TEXT_HPP_
#define TEXT_HPP_

class Text {
  public:
    static void writeAlignLeft(int x, int y, std::string text);
    static void writeAlignCenter(int x, int y, std::string text);
    static void writeAlignRight(int x, int y, std::string text);
};

#endif
