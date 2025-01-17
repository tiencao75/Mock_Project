#include "PlayingMediaController.hpp"
#include "ModelManager.hpp"
#include "PlayingMedia.hpp"
#include "PlaylistController.hpp"
#include "PlaylistLibrary.hpp"
#include "MediaFile.hpp"
#include <iostream>
#include <limits>

PlayingMediaController::PlayingMediaController(ModelManager &modelManager, ViewManager &viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

PlayingMediaController::~PlayingMediaController() {}

void PlayingMediaController::playMediaFile(MediaFile &file) {
    modelManager.getPlayingMedia().setCurrentMediaFile(&file);
    modelManager.getPlayingMedia().play();
    std::cout << "Playing: " << file.getName() << std::endl;
}

void PlayingMediaController::play() {
    modelManager.getPlayingMedia().play();
    std::cout << "Resuming playback." << std::endl;
}

void PlayingMediaController::pause() {
    try {
        modelManager.getPlayingMedia().pause();
    } catch (const std::exception &e) {
        std::cerr << "Error while pausing: " << e.what() << std::endl;
    }
}

void PlayingMediaController::resume() {
    if (modelManager.getPlayingMedia().getIsPaused()) {
        modelManager.getPlayingMedia().resume();
        std::cout << "Playback resumed." << std::endl;
    } else {
        std::cout << "No media is paused currently." << std::endl;
    }
}

void PlayingMediaController::stop() {
    try {
        modelManager.getPlayingMedia().stop();
    } catch (const std::exception &e) {
        std::cerr << "Error while stopping: " << e.what() << std::endl;
    }
}

void PlayingMediaController::skipToNext() {
    try {
        modelManager.getPlayingMedia().skipToNext();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void PlayingMediaController::skipToPrevious() {
    try {
        modelManager.getPlayingMedia().skipToPrevious();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void PlayingMediaController::adjustVolume(int newVolume) {
    modelManager.getPlayingMedia().adjustVolume(newVolume);
    std::cout << "Volume adjusted to: " << newVolume << std::endl;
}

void PlayingMediaController::play_Playlist(PlaylistLibrary &library) {
    unsigned int playlistIndex;

    std::cout << "Available Playlists:\n";
    for (const auto &[index, playlist] : library.getAllPlaylists()) {
        std::cout << index << ": " << playlist->getName() << "\n";
    }

    std::cout << "Enter the index of the playlist you want to play: ";
    std::cin >> playlistIndex;

    try {
        auto playlist = library.getPlaylistByIndex(playlistIndex);
        modelManager.getPlayingMedia().setPlaylist(playlist);
        std::cout << "Playing playlist: " << playlist->getName() << "\n";
        modelManager.getPlayingMedia().play();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void PlayingMediaController::handleInput() {
    int choice;

    do {
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

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            if (!modelManager.getPlayingMedia().getCurrentMediaFile()) {
                std::cout << "Error: No media file is currently loaded." << std::endl;
            } else {
                play();
            }
            break;
        case 2:
            pause();
            break;
        case 3:
            resume();
            break;
        case 4:
            stop();
            break;
        case 5: {
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

            if (auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID)) {
                playMediaFile(*mediaFile);
            } else {
                std::cout << "Media file not found." << std::endl;
            }
            break;
        }
        case 6:
            play_Playlist(modelManager.getPlaylistLibrary());
            break;
        case 7:
            skipToNext();
            break;
        case 8:
            skipToPrevious();
            break;
        case 9: {
            int newVolume;
            std::cout << "Enter volume level (0 to 128): ";
            std::cin >> newVolume;
            if (std::cin.fail() || newVolume < 0 || newVolume > 128) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between 0 and 128." << std::endl;
            } else {
                adjustVolume(newVolume);
            }
            break;
        }
        case 0:
            std::cout << "Exiting playback menu..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    } while (choice != 0);
}
