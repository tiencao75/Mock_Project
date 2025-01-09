#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include "FileController.hpp"
#include "PlaylistController.hpp"
#include "MediaFileController.hpp"
#include "PlayingMediaController.hpp"
#include "DetailedPlaylistController.hpp"
#include "MetadataController.hpp"

class ControllerManager {



private:
    ModelManager modelManager;
    ViewManager viewManager;

    // FileController fileController;
    // PlaylistController playlistController;
    // MediaFileController mediaFileController;
    // PlayingMediaController playingMediaController;
    // DetailedPlaylistController detailedPlaylistController;
    // MetadataController metadataController;

public:
    ControllerManager();
    // Getters
    ModelManager& getModelManager();
    ViewManager& getViewManager();
    // FileController& getFileController();
    // PlaylistController& getPlaylistController();
    // MediaFileController& getMediaFileController();
    // PlayingMediaController& getPlayingMediaController();
    // DetailedPlaylistController& getDetailedPlaylistController();
    // MetadataController& getMetadataController();

    // Additional methods if needed
    void handleInput(const std::string& input); // Xử lý input từ người dùng
};

#endif // CONTROLLERMANAGER_HPP
