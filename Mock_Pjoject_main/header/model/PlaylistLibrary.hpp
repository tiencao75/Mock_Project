// PlaylistLibrary.h
#ifndef PLAYLISTLIBRARY_H
#define PLAYLISTLIBRARY_H

#include "Playlist.hpp"
#include "MediaFile.hpp"
#include "Metadata.hpp"
#include <vector>
#include <string>
#include <memory>

class PlaylistLibrary
{
private:
    std::vector<std::shared_ptr<Playlist>> playlists;

public:
    // Get all playlists
    std::vector<std::shared_ptr<Playlist>> getAllPlaylists() const;

    // Add a playlist to the library
    void addPlaylist(const std::shared_ptr<Playlist> &playlist);

    // Remove a playlist from the library
    void removePlaylist(const std::shared_ptr<Playlist> &playlist);

    // Get a playlist by name
    std::shared_ptr<Playlist> getPlaylistByName(const std::string &name) const;

    // Clear all playlists
    void clearLibrary();
};

#endif