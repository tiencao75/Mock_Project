#include "MetadataController.hpp"
#include "ModelManager.hpp"
#include "Metadata.hpp"
#include <iostream>

// Constructor
MetadataController::MetadataController(ControllerManager* manager)
    : controllerManager(manager) {
    // No initialization needed for now
}

// Destructor
MetadataController::~MetadataController() {
    // Cleanup if necessary
}

// Method to get metadata of a media file
std::map<std::string, std::string> MetadataController::getMediaFileMetadata(MediaFile& file) {
    // Access the ModelManager to get the Metadata of the media file
    return file.getMetadata().getData();
}

// Method to update metadata of a media file
void MetadataController::updateMediaFileMetadata(MediaFile& file, const std::map<std::string, std::string>& metadata) {
    // Update the metadata of the file by setting the new data
    file.getMetadata().setData(metadata);
    std::cout << "Metadata for file '" << file.getName() << "' has been updated." << std::endl;
}
