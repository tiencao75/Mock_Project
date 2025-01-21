#ifndef PLAYING_MEDIA_CONTROLLER_HPP
#define PLAYING_MEDIA_CONTROLLER_HPP

#include <string>
#include "ModelManager.hpp"
#include "ViewManager.hpp"

class PlayingMediaController {
public:
    // Constructor & Destructor
    PlayingMediaController(ModelManager &modelManager, ViewManager &viewManager);
    ~PlayingMediaController();

    // Existing functions
    void playMediaFile(MediaFile &file);
    void play();
    void pause();
    void resume();
    void stop();
    void skipToNext();
    void skipToPrevious();
    void adjustVolume(size_t newVolume);
    void play_Playlist(PlaylistLibrary &library);
    void handleInput();

    // New function to play video in a separate thread
    void playVideoInThread(const std::string &filePath);

private:
    ModelManager &modelManager;
    ViewManager &viewManager;
};

#endif
