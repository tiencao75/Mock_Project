#include "ViewDetailedPlaylist.hpp"
#include <iostream>

void ViewDetailedPlaylist::show() {
    std::cout << "Displaying Detailed Playlist View..." << std::endl;
}

// void ViewDetailedPlaylist::hide() {
//     std::cout << "Hiding Detailed Playlist View..." << std::endl;
// }

void ViewDetailedPlaylist::update(const std::string& data) {
    std::cout << "Updating Detailed Playlist View with data: " << data << std::endl;
}

std::string ViewDetailedPlaylist::getName() const {
    return "ViewDetailedPlaylist";
}

void ViewDetailedPlaylist::showPlaylistDetails(const Playlist& playlist) {
    std::cout << "Playlist: " << playlist.getName() << std::endl;
    for (const auto& song : playlist.getSongs()) {
        std::cout << "- " << song.second.getName() << std::endl;
    }
}

void ViewDetailedPlaylist::addMediaFileToPlaylist(const MediaFile& file) {
    std::cout << "Adding file " << file.getName() << " to playlist..." << std::endl;
}

void ViewDetailedPlaylist::removeMediaFileFromPlaylist(const MediaFile& file) {
    std::cout << "Removing file " << file.getName() << " from playlist..." << std::endl;
}
