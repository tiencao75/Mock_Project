#include "DetailedPlaylistController.hpp"
#include "PlaylistLibrary.hpp"
#include <stdexcept>

extern PlaylistLibrary playlistLibrary;

Playlist DetailedPlaylistController::getPlaylistDetails(const std::string& playlistName) {
    return playlistLibrary.getPlaylistByName(playlistName);
}

void DetailedPlaylistController::addSongToPlaylist(const std::string& playlistName, const MediaFile& song) {
    Playlist playlist = playlistLibrary.getPlaylistByName(playlistName);
    playlist.addSong(song);
}

void DetailedPlaylistController::removeSongFromPlaylist(const std::string& playlistName, const MediaFile& song) {
    Playlist playlist = playlistLibrary.getPlaylistByName(playlistName);
    playlist.removeSong(song);
}
