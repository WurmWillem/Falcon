#include "editor.hpp"
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
    case controlKey('s'):
        saveFile();
        break;
    case 27:
        mode = Normal;
        break;
    default:
        break;
    }

    switch (mode)
    {
    case Normal:
        processNormalKey(ch);
        break;
    case Insert:
        processInsertKey(ch);
        break;
    }
}

void Editor::processNormalKey(int ch)
{
    switch (ch)
    {
    case 'i':
        mode = Insert;
        break;
    case 'k':
        moveCursorUp();
        break;
    case 'j':
        moveCursorDown();
        break;
    case 'h':
        moveLeft();
        xAfterLastHorMove = xPos;
        break;
    case 'l':
        moveRight();
        xAfterLastHorMove = xPos;
        break;
    case 'w':
        wMotion();
        xAfterLastHorMove = xPos;
        break;
    case 'b':
        bMotion();
        xAfterLastHorMove = xPos;
        break;
    case controlKey('u'):
        for (size_t _ = 0; _ != termRows / 2; ++_)
            moveCursorUp();
        xAfterLastHorMove = xPos;
        break;
    case controlKey('d'):
        for (size_t _ = 0; _ != termRows / 2; ++_)
            moveCursorDown();
        xAfterLastHorMove = xPos;
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
            else if (!std::isalpha(lines[yPos][xPos])
                     && lines[yPos][xPos] != ' ')
            {
                return;
            }
            /*else if (i == lines[yPos].length() - 2) {*/
            /*   moveCursorDown();*/
            /*}*/
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
        if (xAfterLastHorMove > lines[yPos].length() - 1)
        {
            xPos = lines[yPos].length() - 1;
        }
        else
        {
            xPos = xAfterLastHorMove;
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
        if (xAfterLastHorMove > lines[yPos].length() - 1)
        {
            xPos = lines[yPos].length() - 1;
        }
        else
        {
            xPos = xAfterLastHorMove;
        }

        if (yPos > currentRow + termRows - scrollOff
            && currentRow < fileRows - termRows)
        {
            ++currentRow;
        }
        renderLineNumbers();
    }
}
