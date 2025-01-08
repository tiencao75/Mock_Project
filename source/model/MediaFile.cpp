#include "MediaFile.hpp"

MediaFile::MediaFile(const std::string& name, const std::string& path, const std::string& type)
    : name(name), path(path), type(type) {}

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
}

void MediaFile::setType(const std::string& type) {
    this->type = type;
}
