#include "ControllerManager.hpp"

FileController& ControllerManager::getFileController() {
    return fileController;
}

PlaylistController& ControllerManager::getPlaylistController() {
    return playlistController;
}

MediaFileController& ControllerManager::getMediaFileController() {
    return mediaFileController;
}
