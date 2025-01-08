#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <cstddef>
#include <ncurses.h>
#include <string>
#include <vector>

enum Mode
{
    Normal,
    Insert,
};
enum Operator
{
    None,
    D,
};

class Editor
{
private:
    bool quit = false;

    Mode mode = Mode::Normal;
    Operator op = Operator::None;

    size_t termRows;
    size_t termCols;

    size_t scrollOff;

    size_t yPos;
    size_t xPos;
    size_t xAfterLastHorMove;

    size_t currentRow;
    size_t fileRows;

    WINDOW *lineNumWin;
    WINDOW *textBufWin;

    std::string fileName;

    std::vector<std::string> lines;

public:
    Editor();
    ~Editor();

    void initialize();
    void openFile(const char *filename);
    void saveFile();
    void run();

private:
    int readKey();
    void processKeypress(int ch);
    void processNormalKey(int ch);
    void processInsertKey(int ch);

    void insertChar(int ch);

    void renderLines();
    void renderLineNumbers();

    void moveCursor(int xMov);
    size_t wMotion();
    int bMotion(int xMov);

    void moveCursorUp();
    void moveCursorDown();
    void moveRight();
    void moveLeft();
};

constexpr inline int controlKey(int ch) { return ((ch) & 0x1f); }

#endif
