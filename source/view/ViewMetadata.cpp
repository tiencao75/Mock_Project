#include "ViewMetadata.hpp"
#include <iostream>

void ViewMetadata::show() {
        std::cout << "\n";
        std::cout << "=============================================\n";
        std::cout << "         🎵 Metadata Editing Options         \n";
        std::cout << "=============================================\n";
        std::cout << "  1. Edit Title                              \n";
        std::cout << "  2. Edit Artist                             \n";
        std::cout << "  3. Edit Album                              \n";
        std::cout << "  4. Edit Genre                              \n";
        std::cout << "  5. Edit Year                               \n";
        std::cout << "  6. Edit Track                              \n";
        std::cout << "  7. Restore Original Values                 \n";
        std::cout << "  0. Exit Editing                            \n";
        std::cout << "=============================================\n";
}

// void ViewMetadata::hide() {
//     std::cout << "Hiding Metadata View..." << std::endl;
// }

void ViewMetadata::update(const std::string& data) {
    std::cout << data << std::endl;
}

std::string ViewMetadata::getName() const {
    return "ViewMetadata";
}

void ViewMetadata::showFileMetadata(const MediaFile& file) {
    std::cout << "Showing metadata for file: " << file.getName() << std::endl;
}

void ViewMetadata::editFileMetadata(MediaFile& file) {
    std::cout << "Editing metadata for file: " << file.getName() << std::endl;
}
