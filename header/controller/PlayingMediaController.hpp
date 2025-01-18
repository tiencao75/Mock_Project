#ifndef PLAYINGMEDIA_CONTROLLER_HPP
#define PLAYINGMEDIA_CONTROLLER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include "MediaFile.hpp"
#include "PlaylistLibrary.hpp"

class PlayingMediaController
{
private:
    // ControllerManager* controllerManager;
    ModelManager &modelManager;
    ViewManager &viewManager;

public:
    PlayingMediaController(ModelManager &modelManager, ViewManager &viewManager);
    ~PlayingMediaController();

    void playMediaFile(MediaFile &file);
    void play();
    void pause();
    void resume();
    void stop();
    void skipToNext();
    void skipToPrevious();
    void adjustVolume(int newVolume);
    void play_Playlist(PlaylistLibrary &library);
    void handleInput();
};

#endif // PLAYINGMEDIA_CONTROLLER_HPP