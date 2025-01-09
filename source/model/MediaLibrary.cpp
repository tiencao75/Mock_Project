#include "MediaLibrary.hpp"
#include <algorithm>
#include <stdexcept>

MediaLibrary::MediaLibrary() {}
const std::vector<MediaFile> & MediaLibrary::getAllMediaFiles() const {
    return mediaFiles;
}

void MediaLibrary::addMediaFile(const MediaFile& file) {
    mediaFiles.push_back(file);
}

void MediaLibrary::removeMediaFile(const MediaFile& file) {
    mediaFiles.erase(std::remove(mediaFiles.begin(), mediaFiles.end(), file), mediaFiles.end());
}

MediaFile MediaLibrary::getMediaFileByName(const std::string& name) const {
    for (const auto& file : mediaFiles) {
        if (file.getName() == name) {
            return file;
        }
    }
    throw std::runtime_error("File not found");
}

void MediaLibrary::scanDirectory(const std::string& path) {
    // Implementation for scanning directories
}

void MediaLibrary::scanUSBDevice() {
    // Implementation for scanning USB
}
