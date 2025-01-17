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
PlayingMedia::PlayingMedia() : music(nullptr), isPlaying(false), isPaused(false), currentMediaFile(nullptr) 
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

    if (!std::filesystem::exists(filePath))
    {
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
    isPlaying = playing;

    if (!playing)

    {

        isPaused = false; // Đặt trạng thái tạm dừng về false nếu ngừng phát

        std::cout << "Playback stopped or finished." << std::endl;
    }
}
// Check if a media file is paused
bool PlayingMedia::getIsPaused() const
{
    return isPaused;
}


void PlayingMedia::onMusicFinished()

{

    std::cout << "Playback finished." << std::endl;

    // Lấy đối tượng PlayingMedia thông qua singleton

    PlayingMedia &instance = PlayingMedia::getInstance();

    // Cập nhật trạng thái và giải phóng tài nguyên nếu cần

    instance.isPlaying = false;

    if (instance.currentMediaFile)

    {

        std::string type = instance.currentMediaFile->getType();

        if (type == "mp3" || type == "wav")

        {

            Mix_FreeMusic(instance.music);

            instance.music = nullptr;
        }
    }

    std::cout << "Ready to play the current media again." << std::endl;
}

PlayingMedia &PlayingMedia::getInstance()

{

    static PlayingMedia instance;

    return instance;
}

// Play the current media file
void PlayingMedia::play() {
    try {
        if (!currentMediaFile) {
            throw std::runtime_error("No media file is currently loaded.");
        }

        // Nếu nhạc đã phát
        if (isPlaying) {
            if (Mix_PlayingMusic() == 0) {
                isPlaying = false; // Cập nhật trạng thái
            } else {
                std::cout << "Media is already playing." << std::endl;
                return;
            }
        }

        // Nếu đang tạm dừng, tiếp tục phát
        if (isPaused) {
            Mix_ResumeMusic();
            isPlaying = true;
            isPaused = false;
            std::cout << "Playback resumed." << std::endl;
            return;
        }

        std::string filePath = currentMediaFile->getPath();
        std::string fileType = currentMediaFile->getType();

        // Nếu là video, trích xuất audio
        if (fileType == "video" || fileType == "mp4") {
            std::string extractedAudioPath = "./extracted_audio.wav";
            std::string command = "ffmpeg -y -hide_banner -loglevel quiet -i \"" + filePath + "\" -vn -acodec pcm_s16le \"" + extractedAudioPath + "\"";

            std::cout << "Executing FFmpeg command: " << command << std::endl;
            int result = system(command.c_str());

            if (result != 0 || !std::filesystem::exists(extractedAudioPath)) {
                throw std::runtime_error("Failed to extract audio from video.");
            }

            // Chuyển đổi file WAV sang định dạng SDL2-mixer
            std::string convertedAudioPath = "./converted_audio.wav";
            std::string convertCommand = "ffmpeg -y -hide_banner -loglevel quiet -i \"" + extractedAudioPath + "\" -ar 44100 -ac 2 -sample_fmt s16 \"" + convertedAudioPath + "\"";

            std::cout << "Converting audio to SDL2-compatible format: " << convertCommand << std::endl;
            int convertResult = system(convertCommand.c_str());

            if (convertResult != 0 || !std::filesystem::exists(convertedAudioPath)) {
                throw std::runtime_error("Failed to convert audio file to SDL2-mixer compatible format.");
            }

            filePath = convertedAudioPath;
        }

        // Giải phóng nhạc trước đó nếu có
  if (music) {
    std::cout << "Freeing music: " << music << std::endl;
    Mix_FreeMusic(music);
    music = nullptr;  // Đặt lại con trỏ về nullptr để tránh sử dụng lại
} else {
    std::cerr << "Warning: Attempting to free an invalid or null music pointer." << std::endl;
}


        // Tải file audio
        music = Mix_LoadMUS(filePath.c_str());
if (!music) {
    std::cerr << "SDL_Mixer Error (Load): " << Mix_GetError() << std::endl;
    return;  // Trả về nếu không tải được
}


        // Phát nhạc
        if (Mix_PlayMusic(music, 1) == -1) {
            throw std::runtime_error("Failed to play music: " + std::string(Mix_GetError()));
        }

        isPlaying = true;
        isPaused = false;
        std::cout << "Audio is playing: " << currentMediaFile->getName() << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}




// Pause the current media file
void PlayingMedia::pause()
{
    if (isPlaying)

    {

        Mix_PauseMusic();

        isPlaying = false;

        isPaused = true; // Đánh dấu trạng thái tạm dừng

        std::cout << "Playback paused." << std::endl;
    }
}

// Stop the current media file
void PlayingMedia::stop()
{
    if (currentMediaFile)

    {

        // Dừng phát nhạc

        Mix_HaltMusic();

        // Không xóa file tạm, chỉ dừng playback

        isPlaying = false;

        currentTime = 0;

        std::cout << "Playback stopped." << std::endl;
    }

    else

    {

        std::cout << "No media file is currently loaded or playing." << std::endl;
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
// Adjust volume

void PlayingMedia::adjustVolume(int newVolume)

{

    if (newVolume < 0 || newVolume > 128)

    {

        std::cout << "Volume must be between 0 (mute) and 128 (maximum)." << std::endl;

        return;
    }

    volume = newVolume;

    Mix_VolumeMusic(volume);

    std::cout << "Volume adjusted to: " << volume << std::endl;
}