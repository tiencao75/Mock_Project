#ifndef PLAYING_MEDIA_HPP
#define PLAYING_MEDIA_HPP

#include "MediaFile.hpp"
#include <SDL2/SDL_mixer.h>

class PlayingMedia {
private:
    MediaFile* currentMediaFile;
    int currentTime;
    bool isPlaying;
    bool isPaused = false;
    int volume;
    Mix_Music *music; // Con trỏ quản lý tài nguyên âm nhạc

public:
    PlayingMedia();
    ~PlayingMedia();
    MediaFile* getCurrentMediaFile() const;
    int getCurrentTime() const;
    bool getIsPlaying() const;

    void setCurrentMediaFile(MediaFile* mediaFile);
    void setCurrentTime(int time);
    void setIsPlaying(bool playing);
    bool getIsPaused()const;
    static void onMusicFinished();
    static PlayingMedia& getInstance();

    void play();
    void pause();
    void stop();
    void skipToNext();
    void skipToPrevious();
    void skipForward(int seconds);
    void skipBackward(int seconds);
    void adjustVolume(int newVolume);
};

#endif // PLAYING_MEDIA_HPP
