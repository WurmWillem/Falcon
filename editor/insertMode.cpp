#include "editor.ih"
#include <cstdio>

void Editor::processInsertKey(int ch)
{
    switch (ch)
    {
    case controlKey('h'):
        delCharBehind();
        break;
    default:
        insertChar(ch);
        break;
    }
}

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
            lines.insert(lines.begin() + currentRow + yPos, std::string(""));
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

void Editor::delCharBehind()
{
    size_t fileRowsStart = fileRows;

    if (xPos > 0) // cursor not at start of line
    {
        lines[yPos].erase(xPos - 1, 1);
        xPos--;
        renderLineNumbers();
    }
    else if (yPos > 0) // not at top of file
    { 
        // this is basically just dd
        /*lines.erase(lines.begin() + yPos);*/

        xPos = lines[yPos - 1].length();
        lines[yPos - 1] += lines[yPos];

        lines.erase(lines.begin() + yPos);
        yPos--;
        fileRows--;
        renderLineNumbers();
    }

    /*if (currentRow > fileRows - termRows)*/
    /*{*/
    /*    currentRow = fileRows - termRows;*/
    /*    drawLineNumbers();*/
    /*    moveCursorDown();*/
    /*    if (fileRowsStart != fileRows)*/
    /*        moveCursorDown();*/
    /*}*/
}
