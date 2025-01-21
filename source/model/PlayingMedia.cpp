

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/imgutils.h>
}

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
// std::string convertToAudio(const std::string &filePath)
// {
//     std::string extractedAudioPath = "./extracted_audio.wav";
//     std::string command = "ffmpeg -y -hide_banner -loglevel quiet -i \"" + filePath + "\" -vn -acodec pcm_s16le \"" + extractedAudioPath + "\"";
//     if (system(command.c_str()) != 0 || !fs::exists(extractedAudioPath))
//     {
//         throw std::runtime_error("Failed to extract audio from video.");
//     }
//     return extractedAudioPath;
// }
const MediaFile *PlayingMedia::getCurrentMediaFile() const
{
    return currentMediaFile;
}
void PlayingMedia::playVideo(const char *filePath)
{
    AVFormatContext *formatContext = avformat_alloc_context();
    AVCodecContext *codecContext = nullptr;
    const AVCodec *codec = nullptr;
    AVFrame *frame = av_frame_alloc();
    AVFrame *frameRGB = av_frame_alloc();
    AVPacket *packet = av_packet_alloc();
    SwsContext *swsContext = nullptr;
    uint8_t *buffer = nullptr;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture = nullptr;
    int videoStreamIndex = -1;
    int numBytes = 0;
    bool quit = false;

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    // Open video file
    if (avformat_open_input(&formatContext, filePath, nullptr, nullptr) < 0)
    {
        std::cerr << "[ERROR] Could not open video file: " << filePath << std::endl;
        goto cleanup;
    }

    // Retrieve stream information
    if (avformat_find_stream_info(formatContext, nullptr) < 0)
    {
        std::cerr << "[ERROR] Failed to retrieve stream info." << std::endl;
        goto cleanup;
    }

    // Find the video stream
    for (unsigned int i = 0; i < formatContext->nb_streams; i++)
    {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1)
    {
        std::cerr << "[ERROR] No video stream found." << std::endl;
        goto cleanup;
    }

    // Get codec parameters and find decoder
    codec = avcodec_find_decoder(formatContext->streams[videoStreamIndex]->codecpar->codec_id);
    if (!codec)
    {
        std::cerr << "[ERROR] Unsupported codec." << std::endl;
        goto cleanup;
    }

    codecContext = avcodec_alloc_context3(codec);
    if (!codecContext)
    {
        std::cerr << "[ERROR] Failed to allocate codec context." << std::endl;
        goto cleanup;
    }

    if (avcodec_parameters_to_context(codecContext, formatContext->streams[videoStreamIndex]->codecpar) < 0)
    {
        std::cerr << "[ERROR] Failed to copy codec parameters to context." << std::endl;
        goto cleanup;
    }

    if (avcodec_open2(codecContext, codec, nullptr) < 0)
    {
        std::cerr << "[ERROR] Failed to open codec." << std::endl;
        goto cleanup;
    }

    // Prepare for frame conversion
    numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecContext->width, codecContext->height, 1);
    buffer = (uint8_t *)av_malloc(numBytes);
    av_image_fill_arrays(frameRGB->data, frameRGB->linesize, buffer, AV_PIX_FMT_RGB24, codecContext->width, codecContext->height, 1);

    swsContext = sws_getContext(codecContext->width, codecContext->height, codecContext->pix_fmt,
                                codecContext->width, codecContext->height, AV_PIX_FMT_RGB24,
                                SWS_BILINEAR, nullptr, nullptr, nullptr);

    if (!swsContext)
    {
        std::cerr << "[ERROR] Failed to initialize SwsContext." << std::endl;
        goto cleanup;
    }

    // Initialize SDL Video subsystem
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "[ERROR] Failed to initialize SDL Video: " << SDL_GetError() << std::endl;
        goto cleanup;
    }

    window = SDL_CreateWindow("Video Playback", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              codecContext->width, codecContext->height, SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr << "[ERROR] Error creating SDL window: " << SDL_GetError() << std::endl;
        goto cleanup;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cerr << "[ERROR] Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        goto cleanup;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING,
                                codecContext->width, codecContext->height);
    if (!texture)
    {
        std::cerr << "[ERROR] Failed to create SDL texture: " << SDL_GetError() << std::endl;
        goto cleanup;
    }

    // Read frames and display
    SDL_Event event;

    while (!quit && av_read_frame(formatContext, packet) >= 0)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
        }

        if (quit)
            break;

        if (packet->stream_index == videoStreamIndex)
        {
            if (avcodec_send_packet(codecContext, packet) == 0)
            {
                while (avcodec_receive_frame(codecContext, frame) == 0)
                {
                    sws_scale(swsContext, frame->data, frame->linesize, 0, codecContext->height,
                              frameRGB->data, frameRGB->linesize);

                    SDL_UpdateTexture(texture, nullptr, frameRGB->data[0], frameRGB->linesize[0]);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
                    SDL_RenderPresent(renderer);

                    SDL_Delay(40); // Simulate ~25 FPS playback
                }
            }
        }
        av_packet_unref(packet);
        SDL_Delay(10); // Reduce CPU usage
    }

cleanup:
    // Cleanup chỉ dành cho các tài nguyên liên quan đến video
    if (swsContext)
        sws_freeContext(swsContext);
    if (buffer)
        av_free(buffer);
    if (frame)
        av_frame_free(&frame);
    if (frameRGB)
        av_frame_free(&frameRGB);
    if (packet)
        av_packet_free(&packet);
    if (codecContext)
        avcodec_free_context(&codecContext);
    if (formatContext)
        avformat_close_input(&formatContext);
    if (texture)
        SDL_DestroyTexture(texture);
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);

    // Không gọi SDL_Quit() nếu bạn vẫn cần dùng SDL_Mixer
    // SDL_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
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

    if (!currentMediaFile)
    {
        throw std::runtime_error("No media file is currently loaded.");
    }

    if (isPlaying)
    {
        stop();
    }

    std::string filePath = currentMediaFile->getPath();

    if (currentMediaFile->getType() == "audio" || filePath.substr(filePath.find_last_of(".") + 1) == "mp3")
    {
        // Free previous music if any
        if (music)
        {
            Mix_FreeMusic(music);
            music = nullptr;
        }

        // Load new music
        music = Mix_LoadMUS(filePath.c_str());
        if (!music)
        {
            throw std::runtime_error("Failed to load audio: " + std::string(Mix_GetError()));
        }

        // Play the music
        if (Mix_PlayMusic(music, 1) == -1)
        {
            throw std::runtime_error("Failed to play audio: " + std::string(Mix_GetError()));
        }

        isPlaying = true;
        isPaused = false;
        // Tạo luồng riêng cho cửa sổ giao diện
        std::thread mp3WindowThread(&PlayingMedia::showMp3Window, this);
        mp3WindowThread.detach();
    }
    else
    {
        throw std::runtime_error("Unsupported media type: " + filePath);
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
    //std::cout << "Volume adjusted to: " << volume << std::endl;
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
    std::lock_guard<std::mutex> lock(mtx);

    if (!isPlaying && !isPaused)
    {
        std::cout << "No media is currently playing to stop." << std::endl;
        return;
    }

    // Stop music if playing
    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();
        // std::cout << "[DEBUG] Stopped audio playback." << std::endl;
    }

    // Free the current music resource
    if (music)
    {
        Mix_FreeMusic(music);
        music = nullptr;
        // std::cout << "[DEBUG] Freed audio resource." << std::endl;
    }

    isPlaying = false;
    isPaused = false;
    currentTime = 0; // Reset thời gian phát

    if (playbackThread.joinable())
    {
        playbackThread.join();
    }
}

void PlayingMedia::showMp3Window()
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event event;
    TTF_Font *font = nullptr;

    // Khởi tạo SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return;
    }

    // Tải font chữ
    font = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", 24); // Sử dụng Arial
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        return;
    }

    // Tạo cửa sổ và renderer SDL
    window = SDL_CreateWindow("MP3 Playback", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 500, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_Quit();
        return;
    }

    // Vùng nút điều khiển
    SDL_Rect playButton = {50, 300, 100, 50};
    SDL_Rect pauseButton = {200, 300, 100, 50};
    SDL_Rect nextButton = {350, 300, 100, 50};
    SDL_Rect stopButton = {500, 300, 100, 50};
    SDL_Rect volumeBar = {50, 400, 700, 20}; // Thanh âm lượng tổng quát
    SDL_Rect progressBar = {50, 200, 700, 20}; // Thanh tiến trình phát nhạc

    int currentTime = 0; // Bắt đầu thời gian từ 0
    int duration = currentMediaFile->getDuration(); // Lấy thời lượng bài hát
    bool draggingVolume = false; // Biến kiểm tra kéo thanh âm lượng

    bool running = true;
    while (running)
    {
        // Xử lý sự kiện
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
                break;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                SDL_Point mousePoint = {mouseX, mouseY};

                if (SDL_PointInRect(&mousePoint, &playButton))
                {
                    resume(); // Hành động khi nhấn nút Play
                }
                else if (SDL_PointInRect(&mousePoint, &pauseButton))
                {
                    pause(); // Hành động khi nhấn nút Pause
                }
                else if (SDL_PointInRect(&mousePoint, &nextButton))
                {
                    skipToNext(); // Hành động khi nhấn nút Next
                }
                else if (SDL_PointInRect(&mousePoint, &stopButton))
                {
                    stop(); // Hành động khi nhấn nút Stop
                    running = false; // Thoát vòng lặp và đóng cửa sổ
                }
                else if (SDL_PointInRect(&mousePoint, &volumeBar))
                {
                    draggingVolume = true; // Bắt đầu kéo thanh âm lượng
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                draggingVolume = false; // Dừng kéo thanh âm lượng
            }
            else if (event.type == SDL_MOUSEMOTION && draggingVolume)
            {
                int mouseX = event.motion.x;
                if (mouseX >= volumeBar.x && mouseX <= volumeBar.x + volumeBar.w)
                {
                    volume = (mouseX - volumeBar.x) * 128 / volumeBar.w; // Tính lại giá trị âm lượng
                    adjustVolume(volume); // Đồng bộ âm lượng
                }
            }
        }

        // Xóa màn hình
        SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255); // Màu nền trắng
        SDL_RenderClear(renderer);

        // Hiển thị tên bài hát
        SDL_Color textColor = {30, 30, 30, 255}; // Màu chữ xám đậm
        SDL_Surface *titleSurface = TTF_RenderText_Blended(font, currentSongName.c_str(), textColor);
        SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        SDL_Rect titleRect = {50, 50, titleSurface->w, titleSurface->h};
        SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
        SDL_FreeSurface(titleSurface);
        SDL_DestroyTexture(titleTexture);

        // Hiển thị thời gian phát
        int currentMinutes = currentTime / 60;
        int currentSeconds = currentTime % 60;
        int totalMinutes = duration / 60;
        int totalSeconds = duration % 60;
        std::string progressText =
            std::to_string(currentMinutes) + ":" +
            (currentSeconds < 10 ? "0" : "") + std::to_string(currentSeconds) + " / " +
            std::to_string(totalMinutes) + ":" +
            (totalSeconds < 10 ? "0" : "") + std::to_string(totalSeconds);
        SDL_Surface *progressSurface = TTF_RenderText_Blended(font, progressText.c_str(), textColor);
        SDL_Texture *progressTexture = SDL_CreateTextureFromSurface(renderer, progressSurface);
        SDL_Rect progressRect = {50, 120, progressSurface->w, progressSurface->h};
        SDL_RenderCopy(renderer, progressTexture, nullptr, &progressRect);
        SDL_FreeSurface(progressSurface);
        SDL_DestroyTexture(progressTexture);

        // Vẽ thanh tiến trình phát nhạc
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255); // Màu xám nhạt
        SDL_RenderFillRect(renderer, &progressBar);
        SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); // Màu xanh steel blue
        SDL_Rect currentProgressBar = {progressBar.x, progressBar.y, (currentTime * progressBar.w / duration), progressBar.h};
        SDL_RenderFillRect(renderer, &currentProgressBar);

        // Vẽ nền cho thanh âm lượng
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255); // Màu xám nhạt
        SDL_RenderFillRect(renderer, &volumeBar);
        SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); // Màu xanh steel blue
        SDL_Rect currentVolumeBar = {volumeBar.x, volumeBar.y, (volume * volumeBar.w / 128), volumeBar.h};
        SDL_RenderFillRect(renderer, &currentVolumeBar);

        // Hiển thị chữ "Volume: xx%"
        std::string volumeText = "Volume: " + std::to_string(volume * 100 / 128) + "%";
        SDL_Surface *volumeTextSurface = TTF_RenderText_Blended(font, volumeText.c_str(), textColor);
        SDL_Texture *volumeTextTexture = SDL_CreateTextureFromSurface(renderer, volumeTextSurface);
        SDL_Rect volumeTextRect = {volumeBar.x, volumeBar.y - 30, volumeTextSurface->w, volumeTextSurface->h}; // Vị trí trên thanh âm lượng
        SDL_RenderCopy(renderer, volumeTextTexture, nullptr, &volumeTextRect);
        SDL_FreeSurface(volumeTextSurface);
        SDL_DestroyTexture(volumeTextTexture);

        // Vẽ các nút điều khiển với giao diện tối giản
        SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); // Màu xanh steel blue
        SDL_RenderFillRect(renderer, &playButton);
        SDL_RenderFillRect(renderer, &pauseButton);
        SDL_RenderFillRect(renderer, &nextButton);
        SDL_RenderFillRect(renderer, &stopButton);

        // Thêm chữ trên các nút
        SDL_Surface *playTextSurface = TTF_RenderText_Blended(font, "Play", {255, 255, 255, 255});
        SDL_Texture *playTextTexture = SDL_CreateTextureFromSurface(renderer, playTextSurface);
        SDL_Rect playTextRect = {playButton.x + 30, playButton.y + 10, playTextSurface->w, playTextSurface->h};
        SDL_RenderCopy(renderer, playTextTexture, nullptr, &playTextRect);
        SDL_FreeSurface(playTextSurface);
        SDL_DestroyTexture(playTextTexture);

        SDL_Surface *pauseTextSurface = TTF_RenderText_Blended(font, "Pause", {255, 255, 255, 255});
        SDL_Texture *pauseTextTexture = SDL_CreateTextureFromSurface(renderer, pauseTextSurface);
        SDL_Rect pauseTextRect = {pauseButton.x + 20, pauseButton.y + 10, pauseTextSurface->w, pauseTextSurface->h};
        SDL_RenderCopy(renderer, pauseTextTexture, nullptr, &pauseTextRect);
        SDL_FreeSurface(pauseTextSurface);
        SDL_DestroyTexture(pauseTextTexture);

        SDL_Surface *nextTextSurface = TTF_RenderText_Blended(font, "Next", {255, 255, 255, 255});
        SDL_Texture *nextTextTexture = SDL_CreateTextureFromSurface(renderer, nextTextSurface);
        SDL_Rect nextTextRect = {nextButton.x + 30, nextButton.y + 10, nextTextSurface->w, nextTextSurface->h};
        SDL_RenderCopy(renderer, nextTextTexture, nullptr, &nextTextRect);
        SDL_FreeSurface(nextTextSurface);
        SDL_DestroyTexture(nextTextTexture);

        SDL_Surface *stopTextSurface = TTF_RenderText_Blended(font, "Stop", {255, 255, 255, 255});
        SDL_Texture *stopTextTexture = SDL_CreateTextureFromSurface(renderer, stopTextSurface);
        SDL_Rect stopTextRect = {stopButton.x + 30, stopButton.y + 10, stopTextSurface->w, stopTextSurface->h};
        SDL_RenderCopy(renderer, stopTextTexture, nullptr, &stopTextRect);
        SDL_FreeSurface(stopTextSurface);
        SDL_DestroyTexture(stopTextTexture);

        // Cập nhật thời gian phát mỗi giây
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        if (currentTime < duration && !isPaused) // Chỉ tăng thời gian nếu không ở trạng thái Pause
            currentTime++;
    }

    // Cleanup resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
}