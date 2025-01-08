#include "editor.ih"

void Editor::run()
{
    while (!quit)
    {
        processKeypress(readKey());
        renderLines();
    }
}

// This function is the run loop
