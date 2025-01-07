#include "editor.ih"

void Editor::processKeypress(int ch)
{
    switch (ch)
    {
    case controlKey('q'):
        quit = true;
        break;
    case 27:
        quit = true;
        break;
    case 'k':
        keyPressedArrowUp();
        break;
    case 'j':
        keypressedArrowDown();
        break;
    case 'h':
        break;
    case 'l':
        break;
    case controlKey('u'):
        for (size_t ix = 0; ix != term_rows / 2; ++ix)
            keyPressedArrowUp();
        break;
    case controlKey('d'):
        for (size_t ix = 0; ix != term_rows / 2; ++ix)
            keypressedArrowDown();
        break;
    default:
        break;
    }
}
