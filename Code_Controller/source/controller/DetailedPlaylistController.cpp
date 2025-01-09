#include "DetailedPlaylistController.hpp"
#include "ModelManager.hpp"
#include "PlaylistLibrary.hpp"
#include <iostream>

// Constructor
DetailedPlaylistController::DetailedPlaylistController(ControllerManager* manager)
    : controllerManager(manager) {
    // No initialization needed for now
}

// Destructor
DetailedPlaylistController::~DetailedPlaylistController() {
    // Cleanup if necessary
}

// Method to get the details of a specific playlist by name
Playlist DetailedPlaylistController::getPlaylistDetails(const std::string& playlistName) {
    // Access the ModelManager to get the PlaylistLibrary and retrieve the playlist by name
    Playlist* playlist = controllerManager->getModelManager()->getPlaylistLibrary()->getPlaylistByName(playlistName);

    if (playlist != nullptr) {
        return *playlist;
    } else {
        std::cout << "Playlist '" << playlistName << "' not found." << std::endl;
        return Playlist();  // Return an empty playlist if not found
    }
}

// Method to add a media file to a playlist
void DetailedPlaylistController::addMediaFileToPlaylist(const std::string& playlistName, MediaFile& file) {
    // Retrieve the playlist by name
    Playlist* playlist = controllerManager->getModelManager()->getPlaylistLibrary()->getPlaylistByName(playlistName);

    if (playlist != nullptr) {
        // Add the media file to the playlist
        playlist->addSong(file);
        std::cout << "Added media file '" << file.getName() << "' to playlist '" << playlistName << "'." << std::endl;
    } else {
        std::cout << "Playlist '" << playlistName << "' not found." << std::endl;
    }
}

// Method to remove a media file from a playlist
void DetailedPlaylistController::removeMediaFileFromPlaylist(const std::string& playlistName, MediaFile& file) {
    // Retrieve the playlist by name
    Playlist* playlist = controllerManager->getModelManager()->getPlaylistLibrary()->getPlaylistByName(playlistName);

    if (playlist != nullptr) {
        // Remove the media file from the playlist
        playlist->removeSong(file);
        std::cout << "Removed media file '" << file.getName() << "' from playlist '" << playlistName << "'." << std::endl;
    } else {
        std::cout << "Playlist '" << playlistName << "' not found." << std::endl;
    }
}
