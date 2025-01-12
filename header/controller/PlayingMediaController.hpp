#ifndef PLAYINGMEDIACONTROLLER_HPP
#define PLAYINGMEDIACONTROLLER_HPP

#include "ControllerManager.hpp"
#include "MediaFile.hpp"
#include "PlayingMedia.hpp"
#include <vector>

class PlayingMediaController {
private:
    ControllerManager* controllerManager;

public:
    // Constructor
    PlayingMediaController(ControllerManager* manager);

    // Destructor
    ~PlayingMediaController();

    // Method to play a media file
    void playMediaFile(MediaFile& file);

    // Method to play the current media
    void play();

    // Method to pause the current media
    void pause();

    // Method to stop the current media
    void stop();

    // Method to skip to the next media in the playlist
    void skipToNext();

    // Method to skip to the previous media in the playlist
    void skipToPrevious();

    // Method to adjust the volume level
    void adjustVolume(int level);
};

#endif // PLAYINGMEDIACONTROLLER_HPP