#ifndef PLAYINGMEDIA_HPP
#define PLAYINGMEDIA_HPP

#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "MediaFile.hpp"

class PlayingMedia {
private:
    std::shared_ptr<MediaFile> currentMediaFile;  // Media file hiện tại đang phát
    Mix_Music* music;                            // Đối tượng SDL_mixer cho âm nhạc
    bool isPlaying;                              // Trạng thái phát

public:
    // Constructor và Destructor
    PlayingMedia();
    ~PlayingMedia();

    // Truy xuất media hiện tại
    std::shared_ptr<MediaFile> getCurrentMediaFile() const;

    // Đặt media hiện tại
    void setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile);

    // Kiểm tra trạng thái phát
    bool getIsPlaying() const;

    // Phát media
    void play();

    // Tạm dừng media
    void pause();

    // Dừng phát
    void stop();

    // Điều chỉnh âm lượng
    void setVolume(int volume);
};

#endif
