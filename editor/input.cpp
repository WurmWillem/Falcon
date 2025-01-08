#include "editor.ih"
#include <cctype>
#include <cstddef>
#include <cstdio>

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
        yAfterLastHorMov = yPos;
        break;
    case 'l':
        moveRight();
        yAfterLastHorMov = yPos;
        break;
    case 'w':
        wMotion();
        yAfterLastHorMov = yPos;
        break;
    case 'b':
        bMotion();
        yAfterLastHorMov = yPos;
        break;
    case controlKey('u'):
        for (size_t _ = 0; _ != termRows / 2; ++_)
            moveCursorUp();
        yAfterLastHorMov = yPos;
        break;
    case controlKey('d'):
        for (size_t _ = 0; _ != termRows / 2; ++_)
            moveCursorDown();
        yAfterLastHorMov = yPos;
        break;
    default:
        break;
    }
}

void Editor::wMotion()
{
    bool spacePassed = false;
    if (std::isalpha(lines[yPos][xPos]))
    {
        for (size_t i = xPos; i < lines[yPos].length() - 1; i++)
        {
            xPos++;
            if (lines[yPos][xPos] == ' ')
            {
                spacePassed = true;
            }
            else if (spacePassed)
            {
                return;
            }
            if (!std::isalpha(lines[yPos][xPos]) && lines[yPos][xPos] != ' ')
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
            if (lines[yPos][xPos] != ' ')
            {
                return;
            }
        }
    }
}

void Editor::bMotion()
{
    if (xPos <= 0)
    {
        return;
    }

    xPos--;
    if (std::isalpha(lines[yPos][xPos]))
    {
        // move back until no alpha anymore
        for (size_t i = xPos; i > 0; i--)
        {
            xPos--;
            if (!std::isalpha(lines[yPos][xPos]))
            {
                xPos++;
                return;
            }
        }
    }
    else if (lines[yPos][xPos] == ' ')
    {
        // move until no space anymore
        for (size_t i = xPos; i > 0; i--)
        {
            xPos--;
            if (lines[yPos][xPos] != ' ')
            {
                xPos++;
                bMotion();
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
        if (xPos > lines[yPos].length() - 1) {
            xPos = lines[yPos].length() - 1;
        }

        if (yPos - currentRow < scrollOff && currentRow > 0)
        {
            --currentRow;
        }
        renderLineNumbers();
    }
}

void Editor::moveCursorDown()
{
    if (yPos < fileRows)
    {
        ++yPos;
        if (xPos > lines[yPos].length() - 1) {
            xPos = lines[yPos].length() - 1;
        }

        if (yPos > currentRow + termRows - scrollOff && currentRow < fileRows - termRows)
        {
            ++currentRow;
        }
        renderLineNumbers();
    }
}
