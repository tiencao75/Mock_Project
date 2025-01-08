#include "Playlist.hpp"
#include <algorithm> // For std::find
#include <stdexcept> // For exceptions

// Constructor
Playlist::Playlist(const std::string& name) : name(name) {}

// Getter for name
std::string Playlist::getName() const {
    return name;
}

// Getter for songs
std::vector<MediaFile> Playlist::getSongs() const {
    return songs;
}

// Add a song to the playlist
void Playlist::addSong(const MediaFile& song) {
    // Check if the song is already in the playlist
    if (std::find(songs.begin(), songs.end(), song) != songs.end()) {
        throw std::runtime_error("Song already exists in the playlist");
    }
    songs.push_back(song);
}

// Remove a song from the playlist
void Playlist::removeSong(const MediaFile& song) {
    auto it = std::find(songs.begin(), songs.end(), song);
    if (it == songs.end()) {
        throw std::runtime_error("Song not found in the playlist");
    }
    songs.erase(it);
}
