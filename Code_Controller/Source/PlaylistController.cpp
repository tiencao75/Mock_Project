#include "PlaylistController.hpp"
#include <iostream>

void PlaylistController::initialize() {
    std::cout << "Initializing PlaylistController..." << std::endl;
}

std::vector<Playlist> PlaylistController::getAllPlaylists() {
    // Code để lấy danh sách Playlist
    std::cout << "Fetching all playlists..." << std::endl;
    return {}; // Placeholder
}

void PlaylistController::createPlaylist(const std::string& name) {
    std::cout << "Creating playlist: " << name << std::endl;
    // Code để tạo playlist
}

void PlaylistController::deletePlaylist(const std::string& name) {
    std::cout << "Deleting playlist: " << name << std::endl;
    // Code để xóa playlist
}
