#ifndef DETAILEDPLAYLISTCONTROLLER_HPP
#define DETAILEDPLAYLISTCONTROLLER_HPP

#include <string>
#include <vector>
#include "Playlist.h"
#include "MediaFile.h"

class DetailedPlaylistController {
public:
    Playlist getPlaylistDetails(const std::string& playlistName);
    void addSongToPlaylist(const std::string& playlistName, const MediaFile& song);
    void removeSongFromPlaylist(const std::string& playlistName, const MediaFile& song);
};

#endif // DETAILEDPLAYLISTCONTROLLER_HPP
