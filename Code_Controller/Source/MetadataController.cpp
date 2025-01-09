#include "MetadataController.hpp"
#include "Metadata.hpp"

std::map<std::string, std::string> MetadataController::getMediaFileMetadata(const MediaFile& file) {
    return file.getMetadata().getData();
}

void MetadataController::updateMediaFileMetadata(MediaFile& file, const std::map<std::string, std::string>& metadata) {
    Metadata updatedMetadata;
    updatedMetadata.setData(metadata);
    file.setMetadata(updatedMetadata);
}
