#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <cstddef>
#include <ncurses.h>
#include <string>
#include <vector>

class Editor
{
private:
    bool quit = false;

    size_t termRows;
    size_t termCols;

    size_t scrollOff;

    size_t yPos;
    size_t xPos;

    size_t currentRow;
    size_t fileRows;

    WINDOW *lineNumWin;
    WINDOW *textBufWin;

    std::vector<std::string> lines;

public:
    Editor();
    ~Editor();

    void initialize();
    void openFile(const char *filename);
    void run();

private:
    int readKey();
    void processKeypress(int ch);

    void renderLines();
    void renderLineNumbers();
    void wMotion();
    void bMotion();

    void moveCursorUp();
    void moveCursorDown();
    void moveRight();
    void moveLeft();
};

constexpr inline int controlKey(int ch)
{
    return ((ch) & 0x1f);
}

#endif
