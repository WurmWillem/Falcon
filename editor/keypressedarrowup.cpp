#include "editor.ih"

void Editor::keyPressedArrowUp()
{
    if (relative_row > 0)
    {
        --relative_row;
        if (current_row > 0 && relative_row < scrolloff)
        {
            --current_row;
            ++relative_row;
        }
        drawLineNumbers();
    }
}
