#ifndef PLAYLIST_CONTROLLER_HPP
#define PLAYLIST_CONTROLLER_HPP

#include "ControllerBase.hpp"
#include <vector>
#include <string>
#include "Playlist.hpp"

class PlaylistController : public ControllerBase {
public:
    std::vector<Playlist> getAllPlaylists();
    void createPlaylist(const std::string& name);
    void deletePlaylist(const std::string& name);
    void initialize() override;
};

#endif // PLAYLIST_CONTROLLER_HPP
