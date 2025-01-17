#include "ViewPlaylist.hpp"
#include <iostream>

void ViewPlaylist::show() {
    std::cout << "Displaying Playlist View..." << std::endl;
}

void ViewPlaylist::hide() {
    std::cout << "Hiding Playlist View..." << std::endl;
}

void ViewPlaylist::update(const std::string& data) {
    std::cout << "Updating Playlist View with data: " << data << std::endl;
}

std::string ViewPlaylist::getName() const {
    return "ViewPlaylist";
}

void ViewPlaylist::showPlaylistMenu() {
    std::cout << "Playlist Menu: [Create] [Delete] [View]" << std::endl;
}

void ViewPlaylist::showPlaylistList(const std::vector<Playlist>& playlists) {
    std::cout << "Playlists:" << std::endl;
    for (const auto& playlist : playlists) {
        std::cout << "- " << playlist.getName() << std::endl;
    }
}

void ViewPlaylist::selectPlaylist(const Playlist& playlist) {
    std::cout << "Selected Playlist: " << playlist.getName() << std::endl;
}
