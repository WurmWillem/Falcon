#include "editor.ih"

void Editor::openFile(char const *filename)
{
    std::ifstream file(filename);

    if (!file)
        throw std::runtime_error(
            std::string("Could not open file " + std::string(filename) + "\n")
        );

    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();
    fileRows = lines.size();
    fileName = filename;
}

void Editor::saveFile()
{
    std::ofstream file(fileName);

    if (!file)
        throw std::runtime_error(
            std::string("Could not open file " + fileName + "for saving\n")
        );

    for (std::string const &line : lines)
    {
        file << line << '\n';
    }

    file.close();

    std::string msg = "Succesfully saved " + std::to_string(fileRows)
        + " lines to " + fileName.c_str() + "   ";
    wmove(stdscr, termRows - 1, termCols - msg.length());
    wprintw(stdscr, "%s", msg.c_str());
    refresh();
}

// This function opens a filepath from <filesystem> and loads its data
