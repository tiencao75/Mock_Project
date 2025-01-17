#include "MediaFileController.hpp"

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
    // Lấy shared_ptr<MediaFile> từ MediaLibrary
    auto sharedMediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(index);

    // Dereference shared_ptr để trả về MediaFile
    if (sharedMediaFile)
    {
        return *sharedMediaFile;
    }
    else
    {
        // throw std::runtime_error("Media file not found: " + name);
    }
}

void MediaFileController::handleInput()
{
    bool isRunning = true;
    while (isRunning)
    {
        std::cout << "\nMedia Options Menu:\n";
        std::cout << static_cast<int>(MediaMenuOption::ShowAllMediaFiles) << ". Show All Media Files\n";
        std::cout << static_cast<int>(MediaMenuOption::ShowMetadata) << ". Show Metadata\n";
        std::cout << static_cast<int>(MediaMenuOption::BackToMainMenu) << ". Back to Main Menu\n";
        std::cout << "Enter your choice: ";

        int choiceInput;
        std::cin >> choiceInput;
        auto choice = static_cast<MediaMenuOption>(choiceInput);

        switch (choice)
        {
        case MediaMenuOption::ShowAllMediaFiles:
        { // Show All Media Files
            auto mediaFiles = getAllMediaFiles();
            auto *mediaFileView = dynamic_cast<ViewMediaFile *>(viewManager.getView("ViewMediaFile"));

            if (mediaFileView)
            {
                if (mediaFiles.empty())
                {
                    mediaFileView->update("No media files found.");
                }
                else
                {
                    mediaFileView->update("Displaying all media files:");
                    modelManager.getMediaLibrary().getAllMediaFiles();
                    for (const auto &file : mediaFiles)
                    {
                        mediaFileView->update(" - " + file.getName() + " (" + file.getType() + ")");
                    }
                }
            }
            break;
        }
        case MediaMenuOption::ShowMetadata:
{
    // Hiển thị metadata của một file
    auto *metadataView = dynamic_cast<ViewMetadata *>(viewManager.getView("ViewMetadata"));

    if (metadataView)
    {
        try
        {
            // Hiển thị danh sách file với ID
            const auto &mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
            if (mediaFiles.empty())
            {
                metadataView->update("No media files available to show metadata.");
            }
            else
            {
                std::string fileList = "\n=== Available Media Files ===\n";
                fileList += "| ID   | Name                  |\n";
                fileList += "|------|-----------------------|\n";
                for (const auto &[id, file] : mediaFiles)
                {
                    fileList += "| " + std::to_string(id) + "    | " + file->getName();
                    fileList.append(23 - file->getName().size(), ' ');
                    fileList += "|\n";
                }
                fileList += "===============================\n";
                metadataView->update(fileList);

                // Yêu cầu người dùng nhập ID để xem metadata
                metadataView->update("Enter the ID of the file to view metadata: ");
                unsigned int fileID;
                std::cin >> fileID;

                // Lấy file từ ID và hiển thị metadata
                auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
                if (!mediaFile)
                {
                    metadataView->update("Error: File with the provided ID does not exist.");
                }
                else
                {
                    const auto &metadata = mediaFile->getMetadata().getData();
                    if (metadata.empty())
                    {
                        metadataView->update("No metadata available for the selected file.");
                    }
                    else
                    {
                        std::string metadataOutput = "\n=== Metadata for File ===\n";
                        metadataOutput += "| Field         | Value                |\n";
                        metadataOutput += "|---------------|----------------------|\n";
                        for (const auto &[key, value] : metadata)
                        {
                            std::string formattedValue = value.empty() ? "Unknown" : value;
                            std::string row = "| " + key;
                            row.append(15 - key.size(), ' ');
                            row += "| " + formattedValue;
                            row.append(22 - formattedValue.size(), ' ');
                            row += "|\n";
                            metadataOutput += row;
                        }
                        metadataOutput += "===========================\n";
                        metadataView->update(metadataOutput);
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            metadataView->update("An error occurred while fetching metadata: " + std::string(e.what()));
        }
        catch (...)
        {
            metadataView->update("An unknown error occurred while fetching metadata.");
        }
    }
    else
    {
        std::cerr << "Error: Metadata view not available.\n";
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
