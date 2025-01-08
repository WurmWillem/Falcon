#include "editor.ih"
#include <ncurses.h>

void Editor::initialize()
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, termRows, termCols);

    lineNumWin = newwin(termRows, 6, 0, 0);
    textBufWin = newwin(termRows, termCols - 6, 0, 6);

    currentRow = 0;
    scrollOff = 8;
    yPos = 0;
    xPos = 0;
    xAfterLastHorMove = 0;

    /*start_color();*/
    /*init_pair(1, COLOR_GREEN, COLOR_BLACK);*/
    /*attron(COLOR_PAIR(1));*/
    /*//print();*/
    /*attroff(COLOR_PAIR(1));*/

    refresh();
    renderLineNumbers();
    renderLines();
}

// This function enabled rawmode and configures the terminal to the way we want it.
// gets the window size, creates a  window for the line numbers and text buffer.
// prints the line numbers
