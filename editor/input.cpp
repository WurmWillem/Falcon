#include "editor.ih"
#include <cctype>
#include <cstddef>

int Editor::readKey() { return getch(); }

void Editor::processKeypress(int ch)
{
    switch (ch)
    {
    case controlKey('q'):
        quit = true;
        break;
    /*case 27:*/
    /*    quit = true;*/
    /*    break;*/
    case 'k':
        moveCursorUp();
        break;
    case 'j':
        moveCursorDown();
        break;
    case 'h':
        moveLeft();
        break;
    case 'l':
        moveRight();
        break;
    case 'w':
        wMotion();
        break;
    case controlKey('u'):
        for (size_t ix = 0; ix != termRows / 2; ++ix)
            moveCursorUp();
        break;
    case controlKey('d'):
        for (size_t ix = 0; ix != termRows / 2; ++ix)
            moveCursorDown();
        break;
    default:
        break;
    }
}

void Editor::wMotion()
{
    if (std::isalpha(lines[yPos][xPos]))
    {
        for (size_t i = xPos; i < lines[yPos].length() - 1; i++)
        {
            xPos++;
            if (!std::isalpha(lines[yPos][xPos]))
            {
                return;
            }
        }
    }
    else
    {
        for (size_t i = xPos; i < lines[yPos].length() - 1; i++)
        {
            xPos++;
            if (std::isalpha(lines[yPos][xPos]))
            {
                return;
            }
        }
    }
}

void Editor::moveRight()
{
    if (xPos < lines[yPos].length() - 1)
    {
        xPos++;
    }
}

void Editor::moveLeft()
{
    if (xPos > 0)
    {
        xPos--;
    }
}

void Editor::moveCursorUp()
{
    if (yPos > 0)
    {
        --yPos;
        if (currentRow > 0 && yPos < scrollOff)
        {
            --currentRow;
            ++yPos;
        }
        drawLineNumbers();
    }
}

void Editor::moveCursorDown()
{
    if (yPos + currentRow < fileRows - 1)
    {
        ++yPos;
        if (currentRow + termRows - 1 < fileRows
            && yPos + 2 > termRows - scrollOff)
        {
            ++currentRow;
            --yPos;
        }
        drawLineNumbers();
    }
}
