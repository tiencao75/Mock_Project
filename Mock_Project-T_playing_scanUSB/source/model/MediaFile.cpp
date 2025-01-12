// #include "MediaFile.hpp"

// MediaFile::MediaFile(const std::string& name, const std::string& path, const std::string& type)
//     : name(name), path(path), type(type) {}

// std::string MediaFile::getName() const {
//     return name;
// }

// std::string MediaFile::getPath() const {
//     return path;
// }

// std::string MediaFile::getType() const {
//     return type;
// }

// Metadata MediaFile::getMetadata() const {
//     return metadata;
// }

// // Toán tử so sánh ==
// bool MediaFile:: operator==(const MediaFile& other) const {
//     return this->name == other.name;
// }

// // Toán tử so sánh != nếu cần
// bool MediaFile:: operator!=(const MediaFile& other) const {
//     return !(*this == other);
// }

// void MediaFile::setMetadata(const Metadata& metadata) {
//     this->metadata = metadata;
// }

// void MediaFile::setType(const std::string& type) {
//     this->type = type;
// }

#include "MediaFile.hpp"
#include <iostream>

MediaFile::MediaFile(const std::string& name, const std::string& path, const std::string& type)
    : name(name), path(path), type(type) {
    metadata.loadFromFile(path); // Automatically load metadata
std::cout<<"da tao video"<<std::endl;
}

std::string MediaFile::getName() const {
    return name;
}

std::string MediaFile::getPath() const {
    return path;
}

std::string MediaFile::getType() const {
    return type;
}

Metadata MediaFile::getMetadata() const {
    return metadata;
}

void MediaFile::setMetadata(const Metadata& metadata) {
    this->metadata = metadata;
    metadata.saveToFile(path); // Save updated metadata to file
}

void MediaFile::setType(const std::string& type) {
    this->type = type;
}

// Toán tử so sánh ==
bool MediaFile:: operator==(const MediaFile& other) const {
    return this->name == other.name;
}

// Toán tử so sánh != nếu cần
bool MediaFile:: operator!=(const MediaFile& other) const {
    return !(*this == other);
}
