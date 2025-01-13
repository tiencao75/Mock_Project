// #include "MediaFileController.hpp"
// #include "ModelManager.hpp"
// #include "MediaLibrary.hpp"
// #include <iostream>

// // Constructor
// MediaFileController::MediaFileController(ControllerManager* manager)
//     : controllerManager(manager) {
//     // No initialization needed for now
// }

// // Destructor
// MediaFileController::~MediaFileController() {
//     // Cleanup if necessary
// }

// // Method to get all media files
// std::vector<MediaFile> MediaFileController::getAllMediaFiles() {
//     // Access the ModelManager to get all media files from MediaLibrary
//     return controllerManager->getModelManager().getMediaLibrary().getAllMediaFiles();
// }

// // Method to get details of a specific media file by name
// MediaFile MediaFileController::getMediaFileDetails(const std::string& name) {
//     // Access the ModelManager to get the media file by name
//     return controllerManager->getModelManager().getMediaLibrary().getMediaFileByName(name);
// }
#include "MediaFileController.hpp"
#include <stdexcept>


// Constructor
MediaFileController::MediaFileController(ModelManager& modelManager, ViewManager& viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

// Destructor
MediaFileController::~MediaFileController() {}

// Method to get all media files
std::vector<MediaFile> MediaFileController::getAllMediaFiles() {
    std::vector<MediaFile> mediaFiles;
    const auto& mediaMap = modelManager.getMediaLibrary().getAllMediaFiles();

    for (const auto& sharedFile : mediaMap) {
        // Truy cập giá trị shared_ptr trong std::pair
        if (sharedFile.second) { 
            mediaFiles.push_back(*sharedFile.second); // Dereference shared_ptr để lấy MediaFile
        }
    }
    return mediaFiles;
}

// Method to get details of a specific media file by name
MediaFile MediaFileController::getMediaFileDetails(unsigned int index) {
   // Lấy shared_ptr<MediaFile> từ MediaLibrary
    auto sharedMediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(index);

    // Kiểm tra nếu không tìm thấy file
    if (!sharedMediaFile) {
        throw std::runtime_error("Error: Media file not found with the given index.");
    }

    // Dereference shared_ptr để trả về MediaFile
    return *sharedMediaFile;
}
