#include "ViewMenu.hpp"

void ViewMenu::show()
{
    std::cout << "Main Menu:" << std::endl;
    std::cout << "1. Scan View" << std::endl;
    std::cout << "2. Media File View" << std::endl;
    std::cout << "3. Playlist View" << std::endl;
    std::cout << "4. Detailed Playlist View" << std::endl;
    std::cout << "5. Play View" << std::endl;
    std::cout << "6. Metadata View" << std::endl;
    std::cout << "Enter your choice: " << std::endl;
}

void ViewMenu::hide()
{
    std::cout << "Hiding Main Menu..." << std::endl;
}

void ViewMenu::handleInput(const std::string &input)
{
    std::cout << "Handling input for Main Menu: " << input << std::endl;
    // Implement logic for menu input handling
}