#ifndef PLAYLIST_LIBRARY_HPP
#define PLAYLIST_LIBRARY_HPP

#include <vector>
#include "Playlist.hpp"

class PlaylistLibrary {
private:
    std::vector<Playlist> playlists;

public:
    std::vector<Playlist> getAllPlaylists() const;
    void addPlaylist(const Playlist& playlist);
    void removePlaylist(const Playlist& playlist);
    Playlist getPlaylistByName(const std::string& name) const;
};

#endif // PLAYLIST_LIBRARY_HPP
