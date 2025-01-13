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

// Constructor
MediaFileController::MediaFileController(ModelManager& modelManager, ViewManager& viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

// Destructor
MediaFileController::~MediaFileController() {}

// Method to get all media files
std::vector<MediaFile> MediaFileController::getAllMediaFiles() {
    // Lấy danh sách shared_ptr<MediaFile> từ MediaLibrary
    const auto& sharedMediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();

    // Tạo danh sách MediaFile bằng cách sao chép từ shared_ptr
    std::vector<MediaFile> mediaFiles;
    for (const auto& sharedFile : sharedMediaFiles) {
        if (sharedFile) {
            mediaFiles.push_back(*sharedFile); // Dereference shared_ptr để lấy MediaFile
        }
    }
    return mediaFiles;
}

// Method to get details of a specific media file by name
MediaFile MediaFileController::getMediaFileDetails(const std::string& name) {
    // Lấy shared_ptr<MediaFile> từ MediaLibrary
    auto sharedMediaFile = modelManager.getMediaLibrary().getMediaFileByName(name);

    // Dereference shared_ptr để trả về MediaFile
    if (sharedMediaFile) {
        return *sharedMediaFile;
    } else {
        //throw std::runtime_error("Media file not found: " + name);
    }
}
