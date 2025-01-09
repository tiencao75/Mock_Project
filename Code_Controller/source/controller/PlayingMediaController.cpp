#include "PlayingMediaController.hpp"
#include "ModelManager.hpp"
#include "PlayingMedia.hpp"
#include <iostream>

// Constructor
PlayingMediaController::PlayingMediaController(ControllerManager* manager)
    : controllerManager(manager) {
    // No initialization needed for now
}

// Destructor
PlayingMediaController::~PlayingMediaController() {
    // Cleanup if necessary
}

// Method to play a specific media file
void PlayingMediaController::playMediaFile(MediaFile& file) {
    // Access the ModelManager to set the current media to the provided file
    controllerManager->getModelManager()->getPlayingMedia()->setCurrentMediaFile(&file);
    controllerManager->getModelManager()->getPlayingMedia()->play();
    std::cout << "Playing: " << file.getName() << std::endl;
}

// Method to play the current media
void PlayingMediaController::play() {
    // Access the current PlayingMedia and play it
    controllerManager->getModelManager()->getPlayingMedia()->play();
    std::cout << "Resuming playback." << std::endl;
}

// Method to pause the current media
void PlayingMediaController::pause() {
    // Access the current PlayingMedia and pause it
    controllerManager->getModelManager()->getPlayingMedia()->pause();
    std::cout << "Playback paused." << std::endl;
}

// Method to stop the current media
void PlayingMediaController::stop() {
    // Access the current PlayingMedia and stop it
    controllerManager->getModelManager()->getPlayingMedia()->stop();
    std::cout << "Playback stopped." << std::endl;
}

// Method to skip to the next media in the playlist
void PlayingMediaController::skipToNext() {
    // Access the current PlayingMedia and skip to the next media
    controllerManager->getModelManager()->getPlayingMedia()->skiptoNext();
    std::cout << "Skipped to the next media." << std::endl;
}

// Method to skip to the previous media in the playlist
void PlayingMediaController::skipToPrevious() {
    // Access the current PlayingMedia and skip to the previous media
    controllerManager->getModelManager()->getPlayingMedia()->skiptoPrevious();
    std::cout << "Skipped to the previous media." << std::endl;
}

// Method to adjust the volume level
void PlayingMediaController::adjustVolume(int level) {
    // Adjust the volume using the DeviceManager
    controllerManager->getModelManager()->getDeviceManager()->setVolume(level);
    std::cout << "Volume adjusted to level: " << level << std::endl;
}
