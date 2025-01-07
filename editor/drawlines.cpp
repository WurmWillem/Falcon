#include "editor.ih"

void Editor::drawLines()
{
    // move cursor to start
    wmove(textBufWin, 0, 0);
    // draw text
    for (size_t ix = currentRow;
         ix != std::min(currentRow + termRows - 1, fileRows); ++ix)
    {
        wprintw(textBufWin, "%s\n", lines[ix].c_str());
    }

    // move cursor to correct position and refresh screen
    wmove(textBufWin, yPos, xPos);
    wrefresh(textBufWin);
}

// This functions draws the text from the current file onto the screen
