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
    // Access the ModelManager to get all media files from MediaLibrary
    return modelManager.getMediaLibrary().getAllMediaFiles();
}

// Method to get details of a specific media file by name
MediaFile MediaFileController::getMediaFileDetails(const std::string& name) {
    // Access the ModelManager to get the media file by name
    return modelManager.getMediaLibrary().getMediaFileByName(name);
}
