#include "editor.ih"

void Editor::renderLines()
{
    // move cursor to start
    wmove(textBufWin, 0, 0);
    // draw text
    for (size_t ix = currentRow;
         ix < std::min(currentRow + termRows - 1, fileRows); ++ix)
    {
        wprintw(textBufWin, "%s\n", lines[ix].c_str());
    }

    // move cursor to correct position and refresh screen
    wmove(textBufWin, yPos - currentRow, xPos);
    wrefresh(textBufWin);
}

void Editor::renderLineNumbers()
{
    wmove(lineNumWin, 0, 0);
    for (size_t ix = currentRow; ix < std::min(termRows + currentRow, lines.size()); ++ix)
    /*for (size_t ix = currentRow + 1; ix < lines.size() + 1; ++ix)*/
    {
        wprintw(lineNumWin, "%*zu\n", 5, ix + 1);
    }
    wrefresh(lineNumWin);
}

// This functions draws the text from the current file onto the screen
