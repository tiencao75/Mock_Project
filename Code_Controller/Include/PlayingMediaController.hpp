#ifndef PLAYINGMEDIACONTROLLER_HPP
#define PLAYINGMEDIACONTROLLER_HPP

#include "MediaFile.hpp"

class PlayingMediaController {
public:
    void playMediaFile(const MediaFile& file);
    void play();
    void pause();
    void stop();
    void skipToNext();
    void skipToPrevious();
    void adjustVolume(int level);
};

#endif // PLAYINGMEDIACONTROLLER_HPP
