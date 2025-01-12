#ifndef PLAYING_MEDIA_HPP
#define PLAYING_MEDIA_HPP

#include "MediaFile.hpp"

class PlayingMedia {
private:
    MediaFile* currentMediaFile;
    int currentTime;
    bool isPlaying;

public:
    PlayingMedia();
    ~PlayingMedia();
    MediaFile* getCurrentMediaFile() const;
    int getCurrentTime() const;
    bool getIsPlaying() const;

    void setCurrentMediaFile(MediaFile* mediaFile);
    void setCurrentTime(int time);
    void setIsPlaying(bool playing);

    void play();
    void pause();
    void stop();
    void skipToNext();
    void skipToPrevious();
    void skipForward(int seconds);
    void skipBackward(int seconds);
};

#endif // PLAYING_MEDIA_HPP
