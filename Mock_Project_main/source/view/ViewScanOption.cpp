#include "ViewScanOption.hpp"
#include <iostream>

void ViewScanfOption::showScanMenu()
{
    std::cout << "1. Scan Directory\n2. Scan USB Device\n";
}

std::string ViewScanfOption::getDirectoryInput()
{
    std::cout << "Enter directory path: ";
    std::string path;
    std::cin >> path;
    return path;
}
void ViewScanfOption::show()
{
    showScanMenu();
}
void ViewScanfOption::hide()
{
    std::cout << "Hiding Scan Menu.\n";
}
void ViewScanfOption::handleInput(const std::string &input)
{
    if (input == "1")
    {
        std::cout << "Scanning directory...\n";
    }
    else if (input == "2")
    {
        std::cout << "Scanning USB Device...\n";
    }
    else
    {
        std::cout << "Invalid option.\n";
    }
}