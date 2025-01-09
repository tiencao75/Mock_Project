#ifndef DETAILEDPLAYLISTCONTROLLER_HPP
#define DETAILEDPLAYLISTCONTROLLER_HPP

#include "ControllerManager.hpp"
#include "Playlist.hpp"
#include "MediaFile.hpp"
#include <vector>
#include <string>

class DetailedPlaylistController {
private:
    ControllerManager* controllerManager;

public:
    // Constructor
    DetailedPlaylistController(ControllerManager* manager);

    // Destructor
    ~DetailedPlaylistController();

    // Method to get the details of a specific playlist by name
    Playlist getPlaylistDetails(const std::string& playlistName);

    // Method to add a media file to a playlist
    void addMediaFileToPlaylist(const std::string& playlistName, MediaFile& file);

    // Method to remove a media file from a playlist
    void removeMediaFileFromPlaylist(const std::string& playlistName, MediaFile& file);
};

#endif // DETAILEDPLAYLISTCONTROLLER_HPP
