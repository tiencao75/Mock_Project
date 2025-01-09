#ifndef CONTROLLER_MANAGER_HPP
#define CONTROLLER_MANAGER_HPP

#include "FileController.hpp"
#include "PlaylistController.hpp"
#include "MediaFileController.hpp"

class ControllerManager {
private:
    FileController fileController;
    PlaylistController playlistController;
    MediaFileController mediaFileController;

public:
    FileController& getFileController();
    PlaylistController& getPlaylistController();
    MediaFileController& getMediaFileController();
};

#endif // CONTROLLER_MANAGER_HPP
