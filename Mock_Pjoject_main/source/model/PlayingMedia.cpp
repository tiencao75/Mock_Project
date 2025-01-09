#include "PlayingMedia.hpp"
#include <stdexcept>


PlayingMedia::PlayingMedia() : currentMediaFile(nullptr), currentTime(0), isPlaying(false) {}

MediaFile* PlayingMedia::getCurrentMediaFile() const {
    return currentMediaFile;
}

int PlayingMedia::getCurrentTime() const {
    return currentTime;
}

bool PlayingMedia::getIsPlaying() const {
    return isPlaying;
}

void PlayingMedia::setCurrentMediaFile(MediaFile* mediaFile) {
    currentMediaFile = mediaFile;
}

void PlayingMedia::setCurrentTime(int time) {
    currentTime = time;
}

void PlayingMedia::setIsPlaying(bool playing) {
    isPlaying = playing;
}

void PlayingMedia::play() {
    if (!currentMediaFile) {
        throw std::runtime_error("No media file set to play");
    }
    isPlaying = true;
}

void PlayingMedia::pause() {
    if (!isPlaying) {
        throw std::runtime_error("Cannot pause. Media is not playing");
    }
    isPlaying = false;
}

void PlayingMedia::stop() {
    isPlaying = false;
    currentTime = 0;
}

void PlayingMedia::skipToNext() {
    // Placeholder for skipping to next track
}

void PlayingMedia::skipToPrevious() {
    // Placeholder for skipping to previous track
}

void PlayingMedia::skipForward(int seconds) {
    currentTime += seconds;
}

void PlayingMedia::skipBackward(int seconds) {
    currentTime = (currentTime > seconds) ? currentTime - seconds : 0;
}
