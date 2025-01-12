#include "PlayingMedia.hpp"
#include <iostream>
#include <stdexcept>

// Constructor
PlayingMedia::PlayingMedia() : currentMediaFile(nullptr), music(nullptr), isPlaying(false)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        throw std::runtime_error("SDL could not initialize! SDL Error: " + std::string(SDL_GetError()));
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        throw std::runtime_error("SDL_mixer could not initialize! Mix Error: " + std::string(Mix_GetError()));
    }
}

// Destructor
PlayingMedia::~PlayingMedia()
{
    if (music)
    {
        Mix_FreeMusic(music);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

// Truy xuất media hiện tại
std::shared_ptr<MediaFile> PlayingMedia::getCurrentMediaFile() const
{
    return currentMediaFile;
}

// Đặt media hiện tại
void PlayingMedia::setCurrentMediaFile(const std::shared_ptr<MediaFile> &mediaFile)
{
    if (music)
    {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    currentMediaFile = mediaFile;

    // Load file âm nhạc
    if (currentMediaFile)
    {
        music = Mix_LoadMUS(currentMediaFile->getPath().c_str());
        if (!music)
        {
            throw std::runtime_error("Failed to load music: " + std::string(Mix_GetError()));
        }
    }
}

// Kiểm tra trạng thái phát
bool PlayingMedia::getIsPlaying() const
{
    return isPlaying;
}

// Phát media
void PlayingMedia::play()
{
    if (!music)
    {
        throw std::runtime_error("No media file is loaded");
    }
    if (Mix_PlayMusic(music, -1) == -1)
    {
        throw std::runtime_error("Error playing music: " + std::string(Mix_GetError()));
    }
    isPlaying = true;
    std::cout << "Playing: " << currentMediaFile->getName() << std::endl;
}

// Tạm dừng media
void PlayingMedia::pause()
{
    if (!isPlaying)
    {
        return;
    }
    Mix_PauseMusic();
    isPlaying = false;
    std::cout << "Paused: " << currentMediaFile->getName() << std::endl;
}

// Dừng phát
void PlayingMedia::stop()
{
    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();
    }
    isPlaying = false;
    std::cout << "Stopped: " << currentMediaFile->getName() << std::endl;
}

// Điều chỉnh âm lượng
void PlayingMedia::setVolume(int volume)
{
    Mix_VolumeMusic(volume);
    std::cout << "Volume set to: " << volume << std::endl;
}
