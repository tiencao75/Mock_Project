#include "ViewMediaFile.hpp"
#include <iostream>

ViewMediaFile::ViewMediaFile() : currentPage(0) {}

void ViewMediaFile::show() {
    std::cout << "\n";
    std::cout << "=============================================\n";
    std::cout << "              📂 Media Options Menu 📂       \n";
    std::cout << "=============================================\n";
    std::cout << "  1. Show All Media Files                    \n";
    std::cout << "  2. Show Metadata                           \n";
    std::cout << "  0. Back to Main Menu                       \n";
    std::cout << "=============================================\n";

}

// void ViewMediaFile::hide() {
//     std::cout << "Hiding Media File View..." << std::endl;
// }

void ViewMediaFile::update(const std::string& data) {
    std::cout << data << std::endl;
}

std::string ViewMediaFile::getName() const {
    return "ViewMediaFile";
}

void ViewMediaFile::showMediaFilesPage(const std::vector<MediaFile>& files, int page) {
    std::cout << "Page " << page << " of Media Files:" << std::endl;
    for (const auto& file : files) {
        std::cout << "- " << file.getName() << std::endl;
    }
}

void ViewMediaFile::nextPage() {
    std::cout << "Moving to next page..." << std::endl;
    currentPage++;
}

void ViewMediaFile::previousPage() {
    std::cout << "Moving to previous page..." << std::endl;
    if (currentPage > 0) {
        currentPage--;
    }
}
