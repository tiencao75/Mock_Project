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
void PlayingMediaController::playVideoInThread(const std::string &filePath) {
    std::thread videoThread([filePath]() {
        try {
            PlayingMedia::getInstance().playVideo(filePath.c_str());
        } catch (const std::exception &e) {
            std::cerr << "Error during video playback: " << e.what() << std::endl;
        }
    });
    videoThread.detach(); // Chạy thread độc lập
}

void PlayingMediaController::skipToNext()
{
    try
    {
        modelManager.getPlayingMedia().skipToNext();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void PlayingMediaController::skipToPrevious()
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

// void PlayingMediaController::play_Playlist(PlaylistLibrary &library)
// {
//     unsigned int playlistIndex;

//     std::cout << "Available Playlists:\n";
//     for (const auto &[index, playlist] : library.getAllPlaylists())
//     {
//         std::cout << index << ": " << playlist->getName() << "\n";
//     }

//     std::cout << "Enter the index of the playlist you want to play: ";
//     std::cin >> playlistIndex;

//     try
//     {
//         auto playlist = library.getPlaylistByIndex(playlistIndex);
//         modelManager.getPlayingMedia().setPlaylist(playlist);
//         std::cout << "Playing playlist: " << playlist->getName() << "\n";
//         modelManager.getPlayingMedia().play();
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
// }

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

        switch (choice)
        {
        case 1:
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
        case 2:
        {
            pause();
            s32kInterface.sendTime(99, 99);
            break;
        }
        case 3:
        {
            resume();
            try {
                    s32kInterface.sendTime(99, 99); // Gửi thời gian minh họa (1 phút 30 giây)
                } catch (const std::exception& e) {
                    std::cerr << "Error sending time: " << e.what() << std::endl;
                }
            break;
        }
        case 4:
        {
            stop();
            s32kInterface.sendTime(00, 00);
            break;
        }
        case 5:
        {
            const auto &mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
            if (mediaFiles.empty()) {
                std::cout << "No media files available." << std::endl;
                break;
            }

            std::cout << "=== Available Media Files ===\n";
            for (const auto &[id, mediaFile] : mediaFiles) {
                std::cout << id << ": " << mediaFile->getName() << " (" << mediaFile->getType() << ")\n";
            }

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
       case 6:
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
        case 7:
        {
            skipToNext();
            break;
        }
        case 8:
        {
            skipToPrevious();
            break;
        }
        case 9:
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
        case 0:
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
