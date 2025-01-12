#ifndef MODEL_MANAGER_HPP
#define MODEL_MANAGER_HPP

#include "MediaLibrary.hpp"
#include "PlaylistLibrary.hpp"
#include "PlayingMedia.hpp"
#include "DeviceManager.hpp"

class ModelManager {
private:
    MediaLibrary mediaLibrary;
    PlaylistLibrary playlistLibrary;
    PlayingMedia playingMedia;
    DeviceManager deviceManager;
    

public:
    ModelManager() = default;
    MediaLibrary& getMediaLibrary();
    PlaylistLibrary& getPlaylistLibrary();
    PlayingMedia& getPlayingMedia();
    DeviceManager& getDeviceManger();
};

#endif // MODEL_MANAGER_HPP
