#include "editor.ih"

void Editor::processInsertKey(int ch) { insertChar(ch); }

void Editor::insertChar(int ch)
{
    if (ch > 32 && ch < 126)
    {
        lines[currentRow + yPos].insert(xPos, 1, ch);
        ++xPos;
    }
    else if (ch == '\n')
    {
        if (xPos == 0)
        {
            lines.insert(
                lines.begin() + currentRow + yPos, std::string("")
            );
            ++fileRows;
            moveCursorDown();
        }
        else
        {
            lines.insert(
                lines.begin() + currentRow + yPos + 1, std::string("")
            );
            ++fileRows;

            std::string str = lines[currentRow + yPos].substr(xPos);
            lines[currentRow + yPos + 1].append(str);
            lines[currentRow + yPos].erase(
                lines[currentRow + yPos].begin() + xPos,
                lines[currentRow + yPos].end()
            );
        }
    }
}
