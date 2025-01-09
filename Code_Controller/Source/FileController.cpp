#include "FileController.hpp"
#include <iostream>

void FileController::initialize() {
    std::cout << "Initializing FileController..." << std::endl;
}

std::vector<MediaFile> FileController::scanDirectory(const std::string& path) {
    // Code để scan thư mục và trả về danh sách MediaFile
    std::cout << "Scanning directory: " << path << std::endl;
    return {}; // Placeholder
}

std::vector<MediaFile> FileController::scanUSBDevice() {
    // Code để scan USB
    std::cout << "Scanning USB device..." << std::endl;
    return {}; // Placeholder
}
