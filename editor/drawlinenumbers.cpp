#include "editor.ih"

void Editor::drawLineNumbers()
{
    wmove(lineNumWin, 0, 0);
    for (size_t ix = currentRow + 1; ix != currentRow + termRows; ++ix)
    {
        wprintw(lineNumWin, "%*zu\n", 5, ix);
    }
    wrefresh(lineNumWin);
}
