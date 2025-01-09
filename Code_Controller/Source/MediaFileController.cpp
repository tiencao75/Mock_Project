#include "MediaFileController.hpp"
#include <iostream>

void MediaFileController::initialize() {
    std::cout << "Initializing MediaFileController..." << std::endl;
}

std::vector<MediaFile> MediaFileController::getAllMediaFiles() {
    // Code để lấy danh sách MediaFile
    std::cout << "Fetching all media files..." << std::endl;
    return {}; // Placeholder
}

MediaFile MediaFileController::getMediaFileDetails(const std::string& name) {
    // Code để lấy chi tiết của một MediaFile
    std::cout << "Fetching details for media file: " << name << std::endl;
    return MediaFile(); // Placeholder
}
