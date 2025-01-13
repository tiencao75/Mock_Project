#include "ViewScanfOption.hpp"
#include <iostream>

void ViewScanfOption::show() {
    std::cout << "Displaying Scan Option Menu..." << std::endl;
}

void ViewScanfOption::hide() {
    std::cout << "Hiding Scan Option Menu..." << std::endl;
}

void ViewScanfOption::update(const std::string& data) {
    std::cout << "Updating Scan Option View with data: \n" << data << std::endl;
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
