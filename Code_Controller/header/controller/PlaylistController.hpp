#ifndef PLAYLISTCONTROLLER_HPP
#define PLAYLISTCONTROLLER_HPP

#include "ControllerManager.hpp"
#include "Playlist.hpp"
#include <vector>
#include <string>

class PlaylistController {
private:
    ControllerManager* controllerManager;

public:
    // Constructor
    PlaylistController(ControllerManager* manager);

    // Destructor
    ~PlaylistController();

    // Method to get all playlists
    std::vector<Playlist> getAllPlaylists();

    // Method to create a new playlist with the given name
    void createPlaylist(const std::string& name);

    // Method to delete a playlist by its name
    void deletePlaylist(const std::string& name);
};

#endif // PLAYLISTCONTROLLER_HPP
