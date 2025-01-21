#include "PlayingMediaController.hpp"
#include "ModelManager.hpp"
#include "PlayingMedia.hpp"
#include "PlaylistController.hpp"
#include "PlaylistLibrary.hpp"
#include "MediaFile.hpp"
#include "S32K144Interface.hpp"
#include <iostream>
#include <limits>
#include <thread>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

PlayingMediaController::PlayingMediaController(ModelManager &modelManager, ViewManager &viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

PlayingMediaController::~PlayingMediaController() {}

void PlayingMediaController::playMediaFile(MediaFile &file)
{
    modelManager.getPlayingMedia().setCurrentMediaFile(&file);
    modelManager.getPlayingMedia().stop();
    modelManager.getPlayingMedia().play();
    std::cout << "Playing: " << file.getName() << std::endl;
}

void PlayingMediaController::play()
{
    modelManager.getPlayingMedia().play();
    std::cout << "Resuming playback." << std::endl;
}

void PlayingMediaController::pause()
{
    try
    {
        modelManager.getPlayingMedia().pause();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error while pausing: " << e.what() << std::endl;
    }
}

void PlayingMediaController::resume()
{
    if (modelManager.getPlayingMedia().getIsPaused())
    {
        modelManager.getPlayingMedia().resume();
        std::cout << "Playback resumed." << std::endl;
    }
    else
    {
        std::cout << "No media is paused currently." << std::endl;
    }
}

void PlayingMediaController::stop()
{
    try
    {
        modelManager.getPlayingMedia().stop();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error while stopping: " << e.what() << std::endl;
    }
}

void PlayingMediaController::playVideoInThread(const std::string &filePath)
{
    std::thread videoThread([filePath]()
                            {
        try {
            // Lấy tên tệp từ đường dẫn
            std::string fileName = std::filesystem::path(filePath).stem().string();

            // Xác định loại tệp dựa trên phần mở rộng
            std::string fileType = "unknown";
            if (filePath.find(".mp4") != std::string::npos)
            {
                fileType = "video";
            }
            else if (filePath.find(".mp3") != std::string::npos)
            {
                fileType = "audio";
            }

            // Kiểm tra loại tệp hợp lệ
            if (fileType == "unknown")
            {
                throw std::runtime_error("Unsupported file type: " + filePath);
            }

            // Tạo đối tượng MediaFile
            MediaFile mediaFile(fileName, filePath, fileType);

            // Kiểm tra sự tồn tại của tệp
            if (!std::filesystem::exists(mediaFile.getPath()))
            {
                throw std::runtime_error("File does not exist: " + filePath);
            }

            // Thiết lập MediaFile hiện tại
            PlayingMedia &playingMedia = PlayingMedia::getInstance();
            playingMedia.setCurrentMediaFile(&mediaFile);

            // Hiển thị debug
            std::cout << "[DEBUG] Current Media File set to: " << mediaFile.getPath() << std::endl;
            std::cout << "[DEBUG] Current Song Name: " << playingMedia.getCurrentSongName() << std::endl;

            // Gọi hàm phát video
            playingMedia.playVideo(filePath.c_str());
        } catch (const std::exception &e) {
            std::cerr << "Error during video playback: " << e.what() << std::endl;
        } });

    // Chạy thread độc lập
    videoThread.detach();
}

void PlayingMediaController::skipToNext()
{
    modelManager.getPlayingMedia().skipToNext();
}

void PlayingMediaController::skipToPrevious()
{
    modelManager.getPlayingMedia().skipToPrevious();
}

void PlayingMediaController::play_Playlist(PlaylistLibrary &library)
{
    try
    {
        modelManager.getPlayingMedia().skipToPrevious();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void PlayingMediaController::adjustVolume(size_t newVolume)
{
    modelManager.getPlayingMedia().adjustVolume(newVolume);
    //std::cout << "Volume adjusted to: " << newVolume << std::endl;
}


void PlayingMediaController::handleInput()
{
    int choice;
    auto& s32kInterface = S32K144Interface::getInstance(*this);
    do
    {
        viewManager.getCurrentView()->hide();
        viewManager.getView("ViewPlay")->show();

        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        auto selection = static_cast<PlayingOption>(choice);

        switch (selection)
        {
        case PlayingOption::Play:
        {
            if (!modelManager.getPlayingMedia().getCurrentMediaFile())
            {
                std::cout << "Error: No media file is currently loaded." << std::endl;
            }
            else
            {
                play();
            }
            break;
        }
        case PlayingOption::Pause:
        {
            pause();
            s32kInterface.sendTime(99, 99);
            break;
        }
        case PlayingOption::Resume:
        {
            resume();
            try {
                    s32kInterface.sendTime(99, 99); // Gửi thời gian minh họa (1 phút 30 giây)
                } catch (const std::exception& e) {
                    std::cerr << "Error sending time: " << e.what() << std::endl;
                }
            break;
        }
        case PlayingOption::Stop:
        {
            stop();
            s32kInterface.sendTime(00, 00);
            break;
        }
        case PlayingOption::PlaySpecific:
        {
            const auto &mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
            if (mediaFiles.empty())
            {
                std::cout << "No media files available." << std::endl;
                break;
            }

            std::cout << "=== Available Media Files ===\n";
            for (const auto &[id, mediaFile] : mediaFiles)
            {
                std::cout << id << ": " << mediaFile->getName() << " (" << mediaFile->getType() << ")\n";
            }

            // Lưu tất cả các tệp vào vector currentMediaFiles
            auto &playingMedia = modelManager.getPlayingMedia();
            auto &currentMediaFiles = playingMedia.getMediaFiles(); // Giả định bạn đã có vector này

            currentMediaFiles.clear(); // Xóa danh sách cũ
            for (const auto &[id, mediaFile] : mediaFiles)
            {
                if (std::find(currentMediaFiles.begin(), currentMediaFiles.end(), mediaFile.get()) == currentMediaFiles.end())
                {
                    currentMediaFiles.push_back(mediaFile.get()); // Sử dụng con trỏ thô
                }
            }

            // Yêu cầu người dùng chọn tệp để phát
            unsigned int fileID;
            std::cout << "Enter the ID of the media file to play: ";
            std::cin >> fileID;
            auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
            if (mediaFile) {
                // Kiểm tra loại tệp (audio hoặc video)
                if (mediaFile->getType() == "video" || mediaFile->getPath().find(".mp4") != std::string::npos) {
                    // Phát video (MP4)
                    playVideoInThread(mediaFile->getPath());
                } else if (mediaFile->getType() == "audio" || mediaFile->getPath().find(".mp3") != std::string::npos) {
                    // Phát audio
                    playMediaFile(*mediaFile);
                    try {
                            int duration = mediaFile->getDuration();
                            s32kInterface.sendTime(duration / 60, duration % 60); // Gửi thời gian
                            } catch (const std::exception& e) {
                                std::cerr << "Error sending time: " << e.what() << std::endl;
                            }
                } else {
                    std::cout << "Unsupported media type: " << mediaFile->getType() << std::endl;
                }
            } else {
                std::cout << "Media file not found." << std::endl;
            }
            break;
        }
       case PlayingOption::PlayPlaylist:
        {
            unsigned int playlistIndex;

            const auto &playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
            if (playlists.empty()) {
                std::cout << "No playlists available." << std::endl;
                break;
            }

            std::cout << "=== Available Playlists ===\n";
            for (const auto &[index, playlist] : playlists) {
                std::cout << index << ": " << playlist->getName() << "\n";
            }

            std::cout << "Enter the index of the playlist you want to play: ";
            std::cin >> playlistIndex;

            try {
                auto playlist = modelManager.getPlaylistLibrary().getPlaylistByIndex(playlistIndex);
                if (!playlist || playlist->getSongs().empty()) {
                    std::cout << "Playlist is empty or invalid." << std::endl;
                    break;
                }

                // Duyệt qua các bài hát trong playlist
                for (const auto &[id, mediaFile] : playlist->getSongs()) {
                    // Tạo bản sao cục bộ của mediaFile
                    MediaFile tempMediaFile = mediaFile;

                    // Kiểm tra loại tệp
                    if (tempMediaFile.getType() == "video" || tempMediaFile.getPath().find(".mp4") != std::string::npos) {
                        // Phát video (MP4)
                        playVideoInThread(tempMediaFile.getPath());
                    } else if (tempMediaFile.getType() == "audio" || tempMediaFile.getPath().find(".mp3") != std::string::npos) {
                        // Phát audio
                        playMediaFile(tempMediaFile);
                    } else {
                        std::cout << "Unsupported media type: " << tempMediaFile.getType() << std::endl;
                    }
                }
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            break;
        }
        case PlayingOption::Next:
        {
            skipToNext();
            break;
        }
        case PlayingOption::Previous:
        {
            skipToPrevious();
            break;
        }
        case PlayingOption::Volume:
        {
            int newVolume;
            std::cout << "Enter volume level (0 to 128): ";
            std::cin >> newVolume;
            if (std::cin.fail() || newVolume < 0 || newVolume > 128)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between 0 and 128." << std::endl;
            }
            else
            {
                adjustVolume(newVolume);
            }
            break;
        }
        case PlayingOption::Exit:
        {
            //s32kInterface.stopReadingSignal();
            PlayingMedia::getInstance().clearScreen();
            std::cout << "Exiting Playback Menu...\n";
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again.\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        }
    }
    } while (choice != 0);
}
