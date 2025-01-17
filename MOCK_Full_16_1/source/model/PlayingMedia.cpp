#include "PlayingMedia.hpp"
#include <cstdlib> // For system()
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
namespace fs = std::filesystem;

// Constructor
PlayingMedia::PlayingMedia()
    : isPlaying(false), stopPlayback(false), isPaused(false), currentTime(0), volume(100),
      music(nullptr), currentPlaylist(nullptr), currentMediaFile(nullptr)
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

// Singleton instance
PlayingMedia &PlayingMedia::getInstance()
{
    static PlayingMedia instance;
    return instance;
}

// Helper function to convert MP4 to audio
std::string convertToAudio(const std::string &filePath)
{
    std::string extractedAudioPath = "./extracted_audio.wav";
    std::string command = "ffmpeg -y -hide_banner -loglevel quiet -i \"" + filePath + "\" -vn -acodec pcm_s16le \"" + extractedAudioPath + "\"";
    if (system(command.c_str()) != 0 || !fs::exists(extractedAudioPath))
    {
        throw std::runtime_error("Failed to extract audio from video.");
    }
    return extractedAudioPath;
}
const MediaFile *PlayingMedia::getCurrentMediaFile() const
{
    return currentMediaFile;
}

// Set current media file
void PlayingMedia::setCurrentMediaFile(const MediaFile *mediaFile)
{
    if (!mediaFile)
    {
        throw std::runtime_error("Media file cannot be null.");
    }
    if (!fs::exists(mediaFile->getPath()))
    {
        throw std::runtime_error("Media file does not exist: " + mediaFile->getPath());
    }
    currentMediaFile = const_cast<MediaFile *>(mediaFile);
    std::cout << "Media file loaded: " << mediaFile->getPath() << std::endl;
}
void PlayingMedia::setPlaylist(std::shared_ptr<Playlist> playlist)
{
    currentPlaylist = playlist;
    if (currentPlaylist && !currentPlaylist->getSongs().empty())
    {
        currentSong = currentPlaylist->getSongs().begin();
        setCurrentMediaFile(&(currentSong->second));
    }
    else
    {
        currentMediaFile = nullptr;
        std::cerr << "Warning: Playlist is empty or invalid." << std::endl;
    }
}

bool PlayingMedia::getIsPaused() const
{
    return isPaused;
}

// Play the current media file
void PlayingMedia::play()
{
    try
    {
        if (!currentMediaFile)
        {
            throw std::runtime_error("No media file is currently loaded.");
        }

        if (isPlaying)
        {
            stop();
        }

        std::string filePath = currentMediaFile->getPath();
        if (currentMediaFile->getType() == "video" || currentMediaFile->getType() == "mp4")
        {
            filePath = convertToAudio(filePath);
        }

        if (music)
        {
            Mix_FreeMusic(music);
        }

        music = Mix_LoadMUS(filePath.c_str());
        if (!music)
        {
            throw std::runtime_error("SDL_Mixer Error (Load): " + std::string(Mix_GetError()));
        }

        if (Mix_PlayMusic(music, 1) == -1)
        {
            throw std::runtime_error("Failed to play music: " + std::string(Mix_GetError()));
        }

        isPlaying = true;
        isPaused = false;
        currentTime = 0;
        std::cout << "Playback started." << std::endl;

        stopPlayback = false;
        playbackThread = std::thread(&PlayingMedia::playbackLoop, this);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Playback loop
void PlayingMedia::playbackLoop()
{
    try
    {
        int duration = currentMediaFile->getDuration();
        int elapsedTime = currentTime;

        while (isPlaying && elapsedTime < duration)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            elapsedTime++;

            // Cập nhật và in lại menu
            showPlaybackMenu(elapsedTime, duration);

            if (!Mix_PlayingMusic() || stopPlayback)
            {
                isPlaying = false;
                break;
            }
        }

        if (elapsedTime >= duration)
        {
            std::cout << "\nPlayback finished." << std::endl;
        }
        stop();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in playback loop: " << e.what() << std::endl;
    }
}

// Skip to the next file
void PlayingMedia::skipToNext()
{
    if (!currentPlaylist || currentPlaylist->getSongs().empty())
    {
        std::cout << "No playlist loaded or playlist is empty." << std::endl;
        return;
    }

    ++currentSong;
    if (currentSong == currentPlaylist->getSongs().end())
    {
        currentSong = currentPlaylist->getSongs().begin();
    }

    setCurrentMediaFile(&(currentSong->second));
    stop();
    play();
}

// Skip to the previous file
void PlayingMedia::skipToPrevious()
{
    if (!currentPlaylist || currentPlaylist->getSongs().empty())
    {
        std::cout << "No playlist loaded or playlist is empty." << std::endl;
        return;
    }

    if (currentSong == currentPlaylist->getSongs().begin())
    {
        currentSong = currentPlaylist->getSongs().end();
    }

    --currentSong;
    setCurrentMediaFile(&(currentSong->second));
    stop();
    play();
}

// Pause the playback
void PlayingMedia::pause()
{
    if (isPlaying && Mix_PlayingMusic())
    {
        Mix_PauseMusic();
        isPlaying = false;
        isPaused = true;
        std::cout << "Playback paused." << std::endl;
    }
    else
    {
        std::cout << "No media is currently playing to pause." << std::endl;
    }
}

// Resume the playback
void PlayingMedia::resume()
{
    if (isPaused)
    {
        Mix_ResumeMusic();
        isPlaying = true;
        isPaused = false;
        std::cout << "Playback resumed." << std::endl;
    }
    else
    {
        std::cout << "No media is currently paused." << std::endl;
    }
}

// Stop the playback
void PlayingMedia::stop()
{
    if (!isPlaying && !isPaused)
    {
        std::cout << "No media is currently playing to stop." << std::endl;
        return;
    }

    stopPlayback = true;
    if (playbackThread.joinable())
    {
        playbackThread.join();
    }

    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();
    }

    isPlaying = false;
    isPaused = false;
    std::cout << "Playback stopped." << std::endl;
}

// Adjust the volume
void PlayingMedia::adjustVolume(int newVolume)
{
    if (newVolume < 0 || newVolume > 128)
    {
        std::cout << "Volume must be between 0 and 128." << std::endl;
        return;
    }
    volume = newVolume;
    Mix_VolumeMusic(volume);
    std::cout << "Volume adjusted to: " << volume << std::endl;
}

// Display playback progress
void PlayingMedia::displayPlaybackProgress(int currentTime, int duration)
{
    std::cout << "\rPlaying: " << currentTime << "/" << duration << " seconds" << std::flush;
}
void PlayingMedia::showPlaybackMenu(int currentTime, int totalDuration)
{
    std::cout << "=== Media Playback Menu ===\n";
    std::cout << "1. Play Current Media\n";
    std::cout << "2. Pause Current Media\n";
    std::cout << "3. Resume Current Media\n";
    std::cout << "4. Stop Current Media\n";
    std::cout << "5. Play Specific Media File\n";
    std::cout << "6. Play Playlist\n";
    std::cout << "7. Skip to Next Media\n";
    std::cout << "8. Skip to Previous Media\n";
    std::cout << "9. Adjust Volume\n";
    std::cout << "0. Exit Playback Menu\n";

    // In thời gian đã chơi
    std::cout << "Playing: " << currentTime << "/" << totalDuration << " seconds" << std::endl;
}
