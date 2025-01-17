#ifndef PLAYINGMEDIA_HPP
#define PLAYINGMEDIA_HPP

#include <string>
#include <memory>
#include <thread>
#include <map>
#include <SDL2/SDL_mixer.h>
#include "MediaFile.hpp"
#include "PlayList.hpp"

class PlayingMedia
{
public:
    static PlayingMedia &getInstance();

    const MediaFile *getCurrentMediaFile() const;

    void setCurrentMediaFile(const MediaFile *mediaFile);
    void setPlaylist(std::shared_ptr<Playlist> playlist);
    bool getIsPaused() const;
    void play();
    void pause();
    void resume();
    void stop();
    void skipToNext();
    void skipToPrevious();
    void adjustVolume(int newVolume);
    void displayPlaybackProgress(int currentTime, int duration);
    void showPlaybackMenu(int currentTime, int totalDuration);

    ~PlayingMedia();

private:
    PlayingMedia();
    PlayingMedia(const PlayingMedia &) = delete;
    PlayingMedia &operator=(const PlayingMedia &) = delete;

    void playbackLoop();

    bool isPlaying;
    bool stopPlayback;
    bool isPaused;
    int currentTime;
    int volume;
    Mix_Music *music;

    std::shared_ptr<Playlist> currentPlaylist;
    std::map<unsigned int, MediaFile>::const_iterator currentSong;
    MediaFile *currentMediaFile;

    std::thread playbackThread;
};

std::string convertToAudio(const std::string &filePath);

#endif // PLAYINGMEDIA_HPP
