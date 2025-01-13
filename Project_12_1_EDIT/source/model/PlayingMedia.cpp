#include "PlayingMedia.hpp"
#include <cstdlib> // For system()
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

// Constructor
PlayingMedia::PlayingMedia() : currentMediaFile(nullptr), currentTime(0), isPlaying(false)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        throw std::runtime_error("Failed to initialize SDL_Mixer: " + std::string(Mix_GetError()));
    }
}

// Destructor
PlayingMedia::~PlayingMedia()
{
    Mix_CloseAudio();
    SDL_Quit();
}

// Get the current media file
MediaFile *PlayingMedia::getCurrentMediaFile() const
{
    return currentMediaFile;
}

// Set the current media file
void PlayingMedia::setCurrentMediaFile(MediaFile *mediaFile)
{
    if (!mediaFile)
    {
        throw std::runtime_error("Media file cannot be null.");
    }

    std::string filePath = mediaFile->getPath();
    // std::ifstream file(filePath);
    // if (!file.good())
    // {
    //     throw std::runtime_error("Invalid media file: " + filePath);
    // }
    
    if (!std::filesystem::exists(filePath)) {
        throw std::runtime_error("Media file does not exist: " + filePath);
    }

    currentMediaFile = mediaFile;
    std::cout << "Media file loaded: " << filePath << std::endl;
}

// Get the current playback time
int PlayingMedia::getCurrentTime() const
{
    return currentTime;
}

// Set the current playback time
void PlayingMedia::setCurrentTime(int time)
{
    if (!currentMediaFile)
    {
        throw std::runtime_error("No media file is currently playing.");
    }
    // Note: SDL_Mixer does not support seeking. Implement custom behavior if needed.
    currentTime = time;
}

// Check if a media file is playing
bool PlayingMedia::getIsPlaying() const
{
    return isPlaying;
}

// Set the playing state
void PlayingMedia::setIsPlaying(bool playing)
{
    if (playing && !isPlaying)
    {
        Mix_ResumeMusic();
        std::cout << "Playback resumed." << std::endl;
    }
    else if (!playing && isPlaying)
    {
        Mix_PauseMusic();
        std::cout << "Playback paused." << std::endl;
    }
    isPlaying = playing;
}

// Play the current media file
void PlayingMedia::play()
{
     Mix_Music *music = nullptr;

    try {
        if (!currentMediaFile) {
            throw std::runtime_error("No media file is currently loaded.");
        }

        std::string filePath = currentMediaFile->getPath();
        std::string fileType = currentMediaFile->getType();
        std::cout << "Now playing: " << filePath << " (" << fileType << ")" << std::endl;

        // Trích xuất audio nếu là video
        std::string outputAudioPath = "./extracted_audio.wav";
        if (fileType == "video" || fileType == "mp4") {
            std::string command = "ffmpeg -y -i \"" + filePath + "\" -vn -acodec pcm_s16le \"" + outputAudioPath + "\"";
            int result = system(command.c_str());
            if (result != 0) {
                throw std::runtime_error("FFmpeg command failed. Cannot extract audio from MP4.");
            }
            if (!std::filesystem::exists(outputAudioPath)) {
                throw std::runtime_error("Temporary audio file not created.");
            }
            filePath = outputAudioPath;
        }

        // Phát nhạc
        music = Mix_LoadMUS(filePath.c_str());
        if (!music) {
            throw std::runtime_error("Failed to load audio file: " + filePath + ". SDL_Mixer error: " + Mix_GetError());
        }

        if (Mix_PlayMusic(music, 1) == -1) {
            throw std::runtime_error("Failed to play audio file. SDL_Mixer error: " + std::string(Mix_GetError()));
        }

        std::cout << "Audio is playing..." << std::endl;
        isPlaying = true;

        // Chờ người dùng nhấn Enter
        std::cout << "Press Enter to stop playback..." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Dừng playback và giải phóng tài nguyên
    if (music) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
    }
    isPlaying = false;
   
   
}

// Pause the current media file
void PlayingMedia::pause()
{
    if (isPlaying)
    {
        Mix_PauseMusic();
        isPlaying = false;
        std::cout << "Playback paused." << std::endl;
    }
}

// Stop the current media file
void PlayingMedia::stop()
{
    if (currentMediaFile)
    {
        Mix_HaltMusic();
        isPlaying = false;
        currentTime = 0;
        std::cout << "Playback stopped." << std::endl;
    }
}

// Skip to the next file
void PlayingMedia::skipToNext()
{
    if (!currentMediaFile)
    {
        throw std::runtime_error("No media file is currently playing.");
    }

    // Implement logic for skipping to the next media file if applicable
    std::cout << "Skipping to next media file (logic to be implemented)." << std::endl;
}

// Skip to the previous file
void PlayingMedia::skipToPrevious()
{
    if (!currentMediaFile)
    {
        throw std::runtime_error("No media file is currently playing.");
    }

    // Implement logic for skipping to the previous media file if applicable
    std::cout << "Skipping to previous media file (logic to be implemented)." << std::endl;
}

// Skip forward by a number of seconds
void PlayingMedia::skipForward(int seconds)
{
    if (!currentMediaFile)
    {
        throw std::runtime_error("No media file is currently playing.");
    }

    int newTime = currentTime + seconds;
    currentTime = newTime;
    std::cout << "Skipped forward to: " << currentTime << " seconds." << std::endl;
}

// Skip backward by a number of seconds
void PlayingMedia::skipBackward(int seconds)
{
    if (!currentMediaFile)
    {
        throw std::runtime_error("No media file is currently playing.");
    }

    int newTime = currentTime - seconds;

    if (newTime < 0)
    {
        newTime = 0;
    }

    currentTime = newTime;
    std::cout << "Skipped backward to: " << currentTime << " seconds." << std::endl;
}