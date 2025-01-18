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
    : isPlaying(false), isPaused(false), stopPlayback(false), currentTime(0), volume(100),
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
    stop(); // Dừng playback trước khi hủy đối tượng
    Mix_CloseAudio();
    SDL_Quit();
}
void PlayingMedia::clearScreen()
{
    system("clear"); // Lệnh xóa màn hình cho Linux
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

// Get current media file
void PlayingMedia::setCurrentMediaFile(const MediaFile *mediaFile)
{
    if (!mediaFile || !std::filesystem::exists(mediaFile->getPath()))
    {
        throw std::runtime_error("Invalid or non-existent media file.");
    }

    currentMediaFile = const_cast<MediaFile *>(mediaFile);

    // Lấy tên bài hát từ đường dẫn file
    currentSongName = std::filesystem::path(mediaFile->getPath()).stem().string();

    std::cout << "Media file loaded: " << currentSongName << std::endl;
}
const std::string &PlayingMedia::getCurrentSongName() const
{
    return currentSongName;
}

bool PlayingMedia::getIsPaused() const
{
    return isPaused;
}
// Set current playlist
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

// Play the current media file
void PlayingMedia::play()
{
    std::lock_guard<std::mutex> lock(mtx);

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
            music = nullptr;
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
        stopPlayback = false;
        currentTime = 0;
        std::cout << "Playback started." << std::endl;

        if (playbackThread.joinable())
        {
            playbackThread.join(); // Dừng thread cũ trước khi tạo thread mới
        }

        playbackThread = std::thread(&PlayingMedia::playbackLoop, this);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in play(): " << e.what() << std::endl;
    }
}

// Playback loop
void PlayingMedia::playbackLoop()
{
    try
    {
        int duration = currentMediaFile->getDuration();

        while (!stopPlayback && currentTime < duration)
        {
            if (isPaused)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
            {
                std::lock_guard<std::mutex> lock(mtx);
                currentTime++;
            }

            clearScreen(); // Xóa màn hình trước khi in lại thông tin

            // Cập nhật thanh tiến trình
            displayPlaybackProgress(currentTime, duration);
        }

        if (currentTime >= duration && !stopPlayback)
        {
            std::cout << "\nPlayback finished." << std::endl;
        }

        stopPlayback = true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in playback loop: " << e.what() << std::endl;
    }
}

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

// Pause the playback
void PlayingMedia::pause()
{
    std::lock_guard<std::mutex> lock(mtx);

    if (isPlaying && Mix_PlayingMusic())
    {
        Mix_PauseMusic();
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
    std::lock_guard<std::mutex> lock(mtx);

    if (isPaused)
    {
        Mix_ResumeMusic();
        isPaused = false;
        isPlaying = true;
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
    {
        std::lock_guard<std::mutex> lock(mtx);

        if (!isPlaying && !isPaused)
        {
            std::cout << "Không có nội dung nào đang phát để dừng." << std::endl;
            return;
        }

        stopPlayback = true; // Đặt cờ dừng vòng lặp phát nhạc
        isPlaying = false;
        isPaused = false;
        currentTime = 0; // Đặt lại thời gian phát
    }

    // Chờ thread phát nhạc kết thúc
    if (playbackThread.joinable())
    {
        playbackThread.join();
    }

    // Dừng thread hiển thị tiến trình
    stopProgressDisplayThread();

    // Giải phóng nhạc nếu cần
    if (music)
    {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    std::cout << "Đã dừng phát nhạc và giải phóng tài nguyên." << std::endl;
}

void PlayingMedia::startProgressDisplayThread()
{
    if (progressThread.joinable())
    {
        stopProgressDisplayThread();
    }

    isDisplaying = true;
    progressThread = std::thread([this]()
                                 {
                                     while (isDisplaying)
                                     {
                                         std::lock_guard<std::mutex> lock(mtx);
                                         displayPlaybackProgress(currentTime, currentMediaFile->getDuration());
                                         std::this_thread::sleep_for(std::chrono::seconds(1));
                                     } });
}

void PlayingMedia::stopProgressDisplayThread()
{
    isDisplaying = false;
    if (progressThread.joinable())
    {
        progressThread.join();
    }
}
void PlayingMedia::displayPlaybackProgress(int currentTime, int duration)
{
    clearScreen(); // Xóa màn hình trước khi hiển thị tiến trình
                   // Hiển thị tên bài hát
    // Hiển thị tên bài hát
    std::cout << "\n=======================================\n";
    std::cout << "            🎵 NOW PLAYING 🎵           \n";
    std::cout << "=======================================\n";
    std::cout << "              " << currentSongName << "              \n";
    std::cout << "=======================================\n\n";

    int currentMinutes = currentTime / 60;
    int currentSeconds = currentTime % 60;
    int durationMinutes = duration / 60;
    int durationSeconds = duration % 60;

    int barWidth = 50;
    float progress = static_cast<float>(currentTime) / duration;
    int pos = barWidth * progress;

    // Hiển thị thanh tiến trình
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] "
              << (currentMinutes < 10 ? "0" : "") << currentMinutes << ":"
              << (currentSeconds < 10 ? "0" : "") << currentSeconds << "/"
              << (durationMinutes < 10 ? "0" : "") << durationMinutes << ":"
              << (durationSeconds < 10 ? "0" : "") << durationSeconds
              << " " << std::flush;
    std::cout << "\n=== Media Playback Menu ===\n"
              << "1. Play Current Media\n"
              << "2. Pause Current Media\n"
              << "3. Resume Current Media\n"
              << "4. Stop Current Media\n"
              << "5. Play Specific Media File\n"
              << "6. Play Playlist\n"
              << "7. Skip to Next Media\n"
              << "8. Skip to Previous Media\n"
              << "9. Adjust Volume\n"
              << "0. Exit Playback Menu\n"
              << "Enter your choice: ";
}
