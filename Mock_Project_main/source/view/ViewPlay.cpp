#include "ViewPlay.hpp"
#include <iostream>

void ViewPlay::showPlayerControls()
{
    std::cout << "Player Controls:" << std::endl;
    std::cout << "1. Play/Pause" << std::endl;
    std::cout << "2. Next" << std::endl;
    std::cout << "3. Previous" << std::endl;
    std::cout << "4. Stop" << std::endl;
}

void ViewPlay::showSongInfo(const std::string &file)
{
    std::cout << "Now Playing: " << file << std::endl;
}
void ViewPlay::show()
{
    std::cout << "Showing detailed playlist view..." << std::endl;
}

void ViewPlay::hide()
{
    std::cout << "Hiding detailed playlist view..." << std::endl;
}

void ViewPlay::handleInput(const std::string &input)
{
    std::cout << "Handling input for detailed playlist view: " << input << std::endl;
}