#include "ModelManager.hpp"

MediaLibrary& ModelManager::getMediaLibrary() {
    return mediaLibrary;
}

PlaylistLibrary& ModelManager::getPlaylistLibrary() {
    return playlistLibrary;
}

PlayingMedia& ModelManager::getPlayingMedia() {
    return playingMedia;
}
