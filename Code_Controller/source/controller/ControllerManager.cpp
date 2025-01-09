#include "ControllerManager.hpp"
#include <iostream>

ControllerManager::ControllerManager()
    : fileController(),
      playlistController(),
      mediaFileController(),
      playingMediaController(),
      detailedPlaylistController(),
      metadataController() {}
// Getters
ModelManager& ControllerManager::getModelManager() {
    return modelManager;
}

ViewManager& ControllerManager::getViewManager() {
    return viewManager;
}

// FileController& ControllerManager::getFileController() {
//     return fileController;
// }

// PlaylistController& ControllerManager::getPlaylistController() {
//     return playlistController;
// }

// MediaFileController& ControllerManager::getMediaFileController() {
//     return mediaFileController;
// }

// PlayingMediaController& ControllerManager::getPlayingMediaController() {
//     return playingMediaController;
// }

// DetailedPlaylistController& ControllerManager::getDetailedPlaylistController() {
//     return detailedPlaylistController;
// }

// MetadataController& ControllerManager::getMetadataController() {
//     return metadataController;
// }

// Handle user input
void ControllerManager::handleInput(const std::string& input) {
    if (input == "1") {
        std::cout << "Navigating to Scan Options..." << std::endl;
        viewManager.switchView(viewManager.getView("ViewScanfOption"));
    } else if (input == "2") {
        std::cout << "Navigating to Main Menu..." << std::endl;
        viewManager.switchView(viewManager.getView("ViewMainMenu"));
    } else {
        std::cerr << "Invalid input." << std::endl;
    }
}
