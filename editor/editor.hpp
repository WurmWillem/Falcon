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

    size_t term_rows;
    size_t term_cols;

    size_t scrolloff;
    size_t relative_row;
    size_t current_row;
    size_t file_rows;

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

    void drawLines();
    void drawLineNumbers();

    void keyPressedArrowUp();
    void keypressedArrowDown();
};

constexpr inline int controlKey(int ch)
{
    return ((ch) & 0x1f);
}

#endif
