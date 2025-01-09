#include "ViewMetadata.hpp"
#include <iostream>

void ViewMetadata::show() {
    std::cout << "Displaying Metadata View..." << std::endl;
}

void ViewMetadata::hide() {
    std::cout << "Hiding Metadata View..." << std::endl;
}

void ViewMetadata::update(const std::string& data) {
    std::cout << "Updating Metadata View with data: " << data << std::endl;
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
