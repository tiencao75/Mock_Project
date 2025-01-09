#include "PlayingMediaController.hpp"
#include "PlayingMedia.hpp"
#include "DeviceManager.hpp"

extern PlayingMedia playingMedia;
extern DeviceManager deviceManager;

void PlayingMediaController::playMediaFile(const MediaFile& file) {
    playingMedia.setCurrentMediaFile(&file);
    playingMedia.play();
}

void PlayingMediaController::play() {
    playingMedia.play();
}

void PlayingMediaController::pause() {
    playingMedia.pause();
}

void PlayingMediaController::stop() {
    playingMedia.stop();
}

void PlayingMediaController::skipToNext() {
    playingMedia.skiptoNext();
}

void PlayingMediaController::skipToPrevious() {
    playingMedia.skiptoPrevious();
}

void PlayingMediaController::adjustVolume(int level) {
    deviceManager.setVolume(level);
}
