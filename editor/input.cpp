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
    case 27: // Esc pressed
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
    case 'd':
        op = d;
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
        executeMotion(wMotion());
        break;
    case 'b':
        executeMotion(bMotion(0));
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

void Editor::executeMotion(int x)
{
    switch (op)
    {
    case d:
        del(x);
        break;
    default:
        moveCursor(x);
        break;
    }
}

void Editor::del(int xRange)
{
    lines[yPos].erase(xPos, xRange);
    /*for (int i = 0; i < xRange; i++)*/
    /*{*/
    /*lines[yPos].erase(i, 1);*/
    /*lines[yPos][xPos + i] = '4';*/
    /*}*/
    op = None;
}

void Editor::moveCursor(int xMov)
{
    if (xPos + xMov == lines[yPos].length())
    {
        xMov--;
    }
    xPos += xMov;
    xAfterLastHorMove = xPos;
}

size_t Editor::wMotion()
{
    size_t xMov = 0;
    bool spacePassed = false;

    if (std::isalpha(lines[yPos][xPos]))
    {
        for (size_t i = xPos; i < lines[yPos].length(); i++)
        {
            xMov++;
            if (lines[yPos][xPos + xMov] == ' ')
            {
                spacePassed = true;
            }
            else if (spacePassed)
            {
                return xMov;
            }
            else if (!std::isalpha(lines[yPos][xPos + xMov])
                     && lines[yPos][xPos + xMov] != ' ')
            {
                return xMov;
            }
        }
    }
    else
    {
        for (size_t i = xPos; i < lines[yPos].length(); i++)
        {
            xMov++;
            if (lines[yPos][xPos + xMov] != ' ')
            {
                return xMov;
            }
        }
    }
    return xMov;
}

int Editor::bMotion(int xMov)
{
    if (xPos <= 0)
    {
        return 0;
    }

    xMov--;
    if (std::isalpha(lines[yPos][xPos + xMov]))
    {
        // move back until no alpha anymore
        for (size_t i = xPos + xMov; i > 0; i--)
        {
            xMov--;
            if (!std::isalpha(lines[yPos][xPos + xMov]))
            {
                return xMov + 1;
            }
        }
    }
    else if (lines[yPos][xPos + xMov] == ' ')
    {
        // move until no space anymore
        for (size_t i = xPos + xMov; i > 0; i--)
        {
            xMov--;
            if (lines[yPos][xPos + xMov] != ' ')
            {
                xMov = bMotion(xMov + 1);
                return xMov;
            }
        }
    }
    return xMov;
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
