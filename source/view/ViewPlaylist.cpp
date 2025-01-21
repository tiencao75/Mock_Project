#include "ViewPlaylist.hpp"
#include <iostream>

void ViewPlaylist::show() {
    std::cout << "\n╔══════════════════════════════════════╗\n";
    std::cout << "║            🎵 Playlist Menu 🎵       ║\n";
    std::cout << "╠══════════════════════════════════════╣\n";
    std::cout << "║  [1] ➤ Create Playlist               ║\n";
    std::cout << "║  [2] ➤ Delete Playlist               ║\n";
    std::cout << "║  [3] ➤ View All Playlists            ║\n";
    std::cout << "║  [4] ➤ Add Song to Playlist          ║\n";
    std::cout << "║  [5] ➤ Remove Song from Playlist     ║\n";
    std::cout << "║  [6] ➤ View Songs in a Playlist      ║\n";
    std::cout << "║  [0] ➤ Exit Playlist Menu            ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
}

// void ViewPlaylist::hide() {
//     std::cout << "Hiding Playlist View..." << std::endl;
// }

void ViewPlaylist::update(const std::string& data) {
    std::cout << "Updating Playlist View with data: " << data << std::endl;
}

std::string ViewPlaylist::getName() const {
    return "ViewPlaylist";
}

void ViewPlaylist::showPlaylistMenu() {

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
