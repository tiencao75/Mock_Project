#ifndef MODEL_MANAGER_HPP
#define MODEL_MANAGER_HPP

#include "MediaLibrary.hpp"
#include "PlaylistLibrary.hpp"
#include "PlayingMedia.hpp"


class ModelManager {
private:
    MediaLibrary mediaLibrary;
    PlaylistLibrary playlistLibrary;
    PlayingMedia playingMedia;
    

public:
    ModelManager() = default;
    MediaLibrary& getMediaLibrary();
    PlaylistLibrary& getPlaylistLibrary();
    PlayingMedia& getPlayingMedia();
};

#endif // MODEL_MANAGER_HPP
