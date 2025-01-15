// #ifndef PLAYLISTCONTROLLER_HPP
// #define PLAYLISTCONTROLLER_HPP

// #include "ControllerManager.hpp"
// #include "PlayList.hpp"
// #include <vector>
// #include <string>

// class PlaylistController {
// private:
//     ControllerManager* controllerManager;

// public:
//     // Constructor
//     PlaylistController(ControllerManager* manager);

//     // Destructor
//     ~PlaylistController();

//     // Method to get all playlists
//     std::vector<Playlist> getAllPlaylists();

//     // Method to create a new playlist with the given name
//     void createPlaylist(const std::string& name);

//     // Method to delete a playlist by its name
//     void deletePlaylist(const std::string& name);
// };

// #endif // PLAYLISTCONTROLLER_HPP

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

    void writeDataToFileFormatted(const std::string& filename, const std::map<std::string, std::string>& data);

};

#endif // PLAYLISTCONTROLLER_HPP