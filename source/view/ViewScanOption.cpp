#include "ViewScanfOption.hpp"
#include <iostream>

void ViewScanfOption::show() {
    std::cout << "\n";
    std::cout << "=============================================\n";
    std::cout << "               📂 SCAN MENU 📂               \n";
    std::cout << "=============================================\n";
    std::cout << "  1. Add or update default directory         \n";
    std::cout << "  2. Use default directory                   \n";
    std::cout << "  3. Enter custom directory path             \n";
    std::cout << "  4. Scan USB devices                        \n";
    std::cout << "=============================================\n";
    std::cout << "👉 Please select an option (1-4): ";
}

// void ViewScanfOption::hide() {
//     std::cout << "Hiding Scan Option Menu..." << std::endl;
// }

void ViewScanfOption::update(const std::string& data) {
    std::cout << "Updating Scan Option View with data: " << data << std::endl;
}

std::string ViewScanfOption::getName() const {
    return "ViewScanfOption";
}

void ViewScanfOption::showScanMenu() {
    std::cout << "1. Scan Directory\n2. Scan USB Device\nEnter your choice: ";
}

std::string ViewScanfOption::getDirectoryInput() {
    std::string path;
    std::cout << "Enter directory path: ";
    std::cin >> path;
    return path;
}
