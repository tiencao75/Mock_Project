#ifndef PLAYLISTCONTROLLER_HPP
#define PLAYLISTCONTROLLER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include <map>
#include <memory>
#include <string>

enum class PlaylistOption{
    Exit,
    Create,
    Delete,
    ViewPlaylist,
    AddSong,
    RemoveSong,
    ViewSong
};

class PlaylistController {
private:
    ModelManager& modelManager;
    ViewManager& viewManager;

public:
    // Constructor
    PlaylistController(ModelManager& modelManager, ViewManager& viewManager);

    // Destructor
    ~PlaylistController();

    // Method to handle user input for managing playlists
    void handleInput();

    // Save playlist data to a file (formatted)
    void writePlaylistsToFile(const std::string& filename) ;
    // void readPlaylistsFromFile(const std::string& filename) ;
};

#endif // PLAYLISTCONTROLLER_HPP
