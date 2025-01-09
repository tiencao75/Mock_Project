#include "PlayList.hpp"
#include <algorithm> // For std::find
#include <stdexcept> // For exceptions

// Constructor
Playlist::Playlist(const std::string &name) : name(name) {}

// Getter for name
std::string Playlist::getName() const
{
    return name;
}

// Getter for songs
std::vector<std::shared_ptr<MediaFile>> Playlist::getSongs() const
{
    return Songs;
}

// Add a song to the playlist
void Playlist::addSong(const std::shared_ptr<MediaFile> &song)
{
    if (std::find(Songs.begin(), Songs.end(), song) == Songs.end())
    {
        Songs.push_back(song);
    }
    else
    {
        throw std::runtime_error("Song already exists in the playlist.");
    }
}

// Remove a song from the playlist
void Playlist::removeSong(const std::shared_ptr<MediaFile> &song)
{
    auto it = std::find(Songs.begin(), Songs.end(), song);
    if (it != Songs.end())
    {
        Songs.erase(it);
    }
    else
    {
        throw std::runtime_error("Song not found in the playlist.");
    }
}