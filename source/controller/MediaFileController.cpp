#include "MediaFileController.hpp"
#include "ExceptionLib.hpp"
#include <iomanip>

// Constructor
MediaFileController::MediaFileController(ModelManager &modelManager, ViewManager &viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

// Destructor
MediaFileController::~MediaFileController() {}

// Method to get all media files
std::vector<MediaFile> MediaFileController::getAllMediaFiles()
{
    std::vector<MediaFile> mediaFiles;
    const auto &mediaMap = modelManager.getMediaLibrary().getAllMediaFiles();

    for (const auto &sharedFile : mediaMap)
    {
        // Truy cập giá trị shared_ptr trong std::pair
        if (sharedFile.second)
        {
            mediaFiles.push_back(*sharedFile.second); // Dereference shared_ptr để lấy MediaFile
        }
    }
    return mediaFiles;
}

// Method to get details of a specific media file by name
MediaFile MediaFileController::getMediaFileDetails(unsigned int index)
{
    try
    {
        auto sharedMediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(index);

        if (sharedMediaFile)
        {
            return *sharedMediaFile;
        }
        else
        {
            throw MediaFileNotFoundException("Media file with the given index does not exist.");
        }
    }
    catch (const std::exception &e)
    {
        throw;
    }
}

void MediaFileController::handleInput()
{
    viewManager.getCurrentView()->hide();
    bool isRunning = true;
    while (isRunning)
    {
        viewManager.getCurrentView()->hide();
        viewManager.getView("ViewMediaFile")->show();

        size_t choiceInput;
        Exception_Handler("Enter your choice: ", choiceInput, validateMediaFilesMenu);

        auto choice = static_cast<MediaMenuOption>(choiceInput);

        switch (choice)
        {
        case MediaMenuOption::ShowAllMediaFiles:
        {
            auto mediaFiles = getAllMediaFiles();
            auto *mediaFileView = dynamic_cast<ViewMediaFile *>(viewManager.getView("ViewMediaFile"));

            if (!mediaFileView)
            {
                throw ViewNotFoundException("ViewMediaFile not found.");
            }

            if (mediaFiles.empty())
            {
                mediaFileView->update("No media files found.");
            }
            else
            {
                mediaFileView->update("Displaying all media files:");
                modelManager.getMediaLibrary().displayPaginatedFiles(modelManager.getMediaLibrary().getAllMediaFiles());
            }
            break;
        }
        case MediaMenuOption::ShowMetadata:
        { // Hiển thị metadata của một file
            auto *metadataView = dynamic_cast<ViewMetadata *>(viewManager.getView("ViewMetadata"));

            if (!metadataView)
            {
                throw ViewNotFoundException("ViewMetadata not found.");
            }

            try
            {
                const auto &mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
                if (mediaFiles.empty())
                {
                    metadataView->update("No media files available to show metadata.");
                    viewManager.getCurrentView()->pauseScreen();
                }
                else
                {
                    modelManager.getMediaLibrary().displayPaginatedFiles(mediaFiles);

                    size_t fileID;
                    Exception_Handler("Enter the ID of the file to view metadata: ", fileID, validateID);

                    try
                    {
                        auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
                        const auto &metadata = mediaFile->getMetadata().getData();

                        if (metadata.empty())
                        {
                            metadataView->update("No metadata available for the selected file.");
                            viewManager.getCurrentView()->pauseScreen();
                        }
                        else
                        {
                            viewManager.getCurrentView()->hide();
                             // Để sử dụng std::setw và std::left

                            std::cout << "\n";
                            std::cout << "======================================================================\n";
                            std::cout << "            🎵 Metadata for file:                \n";
                            std::cout << "            '" << mediaFile->getName() << "'    \n";
                            std::cout << "======================================================================\n";

                            for (const auto &[key, value] : metadata) {
                                std::cout << "  " << std::setw(15) << std::left << key   // Key được canh trái, rộng 15 ký tự
                                        << ": " 
                                        << (value.empty() ? "unknown" : value) // Giá trị hiển thị hoặc "unknown" nếu trống
                                        << "\n";
                            }

                            std::cout << "======================================================================\n";

                            while (true)
                            {
                                size_t exitCode;
                                Exception_Handler("Enter 0 to exit: ", exitCode, validatePosInteger);

                        if (exitCode == 0)
                        {
                            metadataView->update("Exiting metadata view...");
                            viewManager.getCurrentView()->pauseScreen();
                            break;
                        }
                        else
                        {
                            metadataView->update("Invalid input. Please enter 0 to exit.");
                        }
                    }
                }
            }
            catch (const std::out_of_range &e)
            {
                metadataView->update(std::string("Error: ") + e.what());
                metadataView->update("Please try again.");
                viewManager.getCurrentView()->pauseScreen();
            }
        }
    }
    catch (const std::exception &e)
    {
        metadataView->update("An error occurred while fetching metadata: " + std::string(e.what()));
        viewManager.getCurrentView()->pauseScreen();
    }
    catch (...)
    {
        metadataView->update("An unknown error occurred while fetching metadata.");
        viewManager.getCurrentView()->pauseScreen();
    }
    break;
}


        case MediaMenuOption::BackToMainMenu:
        { // Back to Main Menu
            isRunning = false;
            break;
        }
        default:
        {
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
        }
    }
}
