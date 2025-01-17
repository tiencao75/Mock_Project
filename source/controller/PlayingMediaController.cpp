#include "PlayingMediaController.hpp"
#include "ModelManager.hpp"
#include "PlayingMedia.hpp"
#include <limits>
#include <iostream>

// Constructor
// PlayingMediaController::PlayingMediaController(ControllerManager* manager)
//     : controllerManager(manager) {
//     // No initialization needed for now
// }

PlayingMediaController::PlayingMediaController(ModelManager &modelManager, ViewManager &viewManager) : modelManager(modelManager), viewManager(viewManager) {}

// Destructor
PlayingMediaController::~PlayingMediaController()
{
    // Cleanup if necessary
}

// Method to play a specific media file
void PlayingMediaController::playMediaFile(MediaFile &file)
{
    // Access the ModelManager to set the current media to the provided file
    modelManager.getPlayingMedia().setCurrentMediaFile(&file);
    modelManager.getPlayingMedia().play();
    std::cout << "Playing: " << file.getName() << std::endl;
}

// Method to play the current media
void PlayingMediaController::play()
{
    // Access the current PlayingMedia and play it
    modelManager.getPlayingMedia().play();
    std::cout << "Resuming playback." << std::endl;
}

// Method to pause the current media
void PlayingMediaController::pause()
{
    // Access the current PlayingMedia and pause it
    modelManager.getPlayingMedia().pause();
    std::cout << "Playback paused." << std::endl;
}
void PlayingMediaController::resume()

{

    if (modelManager.getPlayingMedia().getIsPaused()) // Kiểm tra trạng thái tạm dừng

    {

        modelManager.getPlayingMedia().play(); // Tiếp tục phát
    }

    else

    {

        std::cout << "No media is paused currently." << std::endl;
    }
}

// Method to stop the current media
void PlayingMediaController::stop()
{
    // Access the current PlayingMedia and stop it
    modelManager.getPlayingMedia().stop();
    std::cout << "Playback stopped." << std::endl;
}

// Method to skip to the next media in the playlist
void PlayingMediaController::skipToNext()
{
    // Access the current PlayingMedia and skip to the next media
    modelManager.getPlayingMedia().skipToNext();
    std::cout << "Skipped to the next media." << std::endl;
}

// Method to skip to the previous media in the playlist
void PlayingMediaController::skipToPrevious()
{
    // Access the current PlayingMedia and skip to the previous media
    modelManager.getPlayingMedia().skipToPrevious();
    std::cout << "Skipped to the previous media." << std::endl;
}
void PlayingMediaController::adjustVolume(int newVolume)

{

    modelManager.getPlayingMedia().adjustVolume(newVolume);

    std::cout << "Update volume to: " << newVolume << std::endl;
}

void PlayingMediaController::handleInput()
{
    modelManager.getMediaLibrary().clearScreen();
    int choice;
    auto &playingMedia = modelManager.getPlayingMedia();

    do
    {
        // Hiển thị menu lựa chọn

        std::cout << "\n=== Media Playback Menu ===\n";

        std::cout << "1. Play Current Media\n";

        std::cout << "2. Pause Current Media\n";

        std::cout << "3. Resume Current Media\n";

        std::cout << "4. Stop Current Media\n";

        std::cout << "5. Play Specific Media File\n";

        std::cout << "6. Skip to Next Media\n";

        std::cout << "7. Skip to Previous Media\n";

        std::cout << "8. Adjust Volume\n";

        std::cout << "0. Exit Playback Menu\n";

        std::cout << "Enter your choice: ";

        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore();

        switch (choice)
        {
        case 1:

            if (!modelManager.getPlayingMedia().getCurrentMediaFile())

            {

                std::cout << "Error: No media file is currently loaded in the playlist." << std::endl;
            }

            else

            {

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

        case 5:

        {

            const auto &mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();

            if (mediaFiles.empty())

            {

                std::cout << "No media files available." << std::endl;

                break;
            }

            std::cout << "=== Available Media Files ===" << std::endl;

            for (const auto &[id, mediaFile] : mediaFiles)

            {

                std::cout << id << ": " << mediaFile->getName() << " (" << mediaFile->getType() << ")" << std::endl;
            }

            // Yêu cầu người dùng nhập ID của tệp cần phát

            std::cout << "Enter the ID of the media file to play: ";

            unsigned int fileID;

            std::cin >> fileID;

            // Kiểm tra input

            if (std::cin.fail())

            {

                std::cout << "Invalid input. Please enter a valid number." << std::endl;

                std::cin.clear();

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                break;
            }

            // Lấy tệp từ MediaLibrary bằng ID

            auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);

            if (!mediaFile)

            {

                std::cout << "Media file not found." << std::endl;
            }

            else

            {

                playMediaFile(*mediaFile); // Gọi hàm phát tệp
            }

            break;
        }

        case 6:

            skipToNext();

            break;

        case 7:

            skipToPrevious();

            break;

        case 8:

        {

            int newVolume;

            std::cout << "Enter volume level (0 to 128): ";

            std::cin >> newVolume;

            if (std::cin.fail())

            {

                std::cout << "Invalid input. Please enter a number between 0 and 128." << std::endl;

                std::cin.clear();

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                break;
            }

            adjustVolume(newVolume);

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
