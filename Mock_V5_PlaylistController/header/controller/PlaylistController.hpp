#ifndef PLAYLISTCONTROLLER_HPP
#define PLAYLISTCONTROLLER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include <vector>
#include <memory>
#include <string>

class PlaylistController {
private:
    ModelManager& modelManager;
    ViewManager& viewManager;

public:
    // Constructor
    PlaylistController(ModelManager& modelManager, ViewManager& viewManager);

    // Destructor
    ~PlaylistController();

    // Method to get all playlists (return shared pointers)
    std::vector<std::shared_ptr<Playlist>> getAllPlaylists();

    // Method to create a new playlist with the given name
    void createPlaylist(const std::string& name);

    // Method to delete a playlist by its name
    void deletePlaylist(const std::string& name);

    // Method to handle user input for managing playlists
    void handleInput();
};

#endif // PLAYLISTCONTROLLER_HPP
