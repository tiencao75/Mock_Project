// PlaylistLibrary.cpp
#include "PlaylistLibrary.hpp"
#include <algorithm>
#include <stdexcept>

// Get all playlists
std::vector<std::shared_ptr<Playlist>> PlaylistLibrary::getAllPlaylists() const
{
    return playlists;
}

// Add a playlist to the library
void PlaylistLibrary::addPlaylist(const std::shared_ptr<Playlist> &playlist)
{
    if (std::find(playlists.begin(), playlists.end(), playlist) == playlists.end())
    {
        playlists.push_back(playlist);
    }
    else
    {
        throw std::runtime_error("Playlist already exists in the library.");
    }
}

// Remove a playlist from the library
void PlaylistLibrary::removePlaylist(const std::shared_ptr<Playlist> &playlist)
{
    auto it = std::find(playlists.begin(), playlists.end(), playlist);
    if (it != playlists.end())
    {
        playlists.erase(it);
    }
    else
    {
        throw std::runtime_error("Playlist not found in the library.");
    }
}

// Get a playlist by name
std::shared_ptr<Playlist> PlaylistLibrary::getPlaylistByName(const std::string &name) const
{
    auto it = std::find_if(playlists.begin(), playlists.end(), [&name](const std::shared_ptr<Playlist> &playlist)
                           { return playlist->getName() == name; });
    if (it != playlists.end())
    {
        return *it;
    }
    else
    {
        throw std::runtime_error("Playlist with the specified name not found.");
    }
}

// Clear all playlists
void PlaylistLibrary::clearLibrary()
{
    playlists.clear();
}