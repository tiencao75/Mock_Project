#ifndef PLAYINGMEDIA_HPP
#define PLAYINGMEDIA_HPP

#include <string>
#include <memory>
#include <thread>
#include <map>
#include <atomic>
#include <mutex>
#include <cstdlib>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include "MediaFile.hpp"
#include "PlayList.hpp"

class PlayingMedia
{
public:
    // Constructor & Destructor
    PlayingMedia();
    ~PlayingMedia();

    // Singleton Instance
    static PlayingMedia &getInstance();

    void clearScreen();   //
    void showMp3Window(); // Hàm hiển thị cửa sổ MP3

    // Getters
    const MediaFile *getCurrentMediaFile() const;
    int getCurrentTime(); // Trả về currentTime và tự động tăng
    const std::string &getCurrentSongName() const;
    bool getIsPaused() const;
    std::vector<MediaFile *> &getMediaFiles();

    // Playback Controls
    void setCurrentMediaFile(const MediaFile *mediaFile);
    void setPlaylist(std::shared_ptr<Playlist> playlist);
    void play();
    void playVideo(const char *filePath); // Play video file (MP4)
    void pause();
    void resume();
    void stop();
    void skipToNext();
    void skipToPrevious();
    void adjustVolume(int newVolume);

    // Display and Progress
    void displayPlaybackProgress(int currentTime, int duration);
    void startProgressDisplayThread(); // Khởi chạy thread hiển thị
    void stopProgressDisplayThread();  // Dừng thread hiển thị

private:
    // Disable Copy Constructor and Assignment Operator
    PlayingMedia(const PlayingMedia &) = delete;
    PlayingMedia &operator=(const PlayingMedia &) = delete;

    // Playback Loop
    void playbackLoop();

    // Thread Management
    std::thread playbackThread;     // Thread phát nhạc
    std::thread progressThread;     // Thread hiển thị tiến trình
    std::atomic<bool> isDisplaying; // Biến kiểm soát hiển thị tiến trình

    // Playback State
    bool isPlaying;
    bool stopPlayback;
    bool isPaused;
    int pausedTime = 0;
    int currentTime;
    int volume;

    // Current Media and Playlist
    Mix_Music *music;
    std::mutex mtx;
    std::shared_ptr<Playlist> currentPlaylist;
    std::map<unsigned int, MediaFile>::const_iterator currentSong;
    MediaFile *currentMediaFile = nullptr;
    std::vector<MediaFile *> mediaFiles;

    std::string currentSongName; // Lưu tên bài hát hiện tại
    std::mutex coutMutex;
};

// Utility Function
// std::string convertToAudio(const std::string &filePath);

#endif // PLAYINGMEDIA_HPP
