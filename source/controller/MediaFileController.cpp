#include "MediaFileController.hpp"

// Constructor
MediaFileController::MediaFileController(ModelManager& modelManager, ViewManager& viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

// Destructor
MediaFileController::~MediaFileController() {}

// Method to get all media files
std::vector<MediaFile> MediaFileController::getAllMediaFiles() {
    // Lấy danh sách shared_ptr<MediaFile> từ MediaLibrary
    const auto& sharedMediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();

    // Tạo danh sách MediaFile bằng cách sao chép từ shared_ptr
    std::vector<MediaFile> mediaFiles;
    for (const auto& sharedFile : sharedMediaFiles) {
        if (sharedFile) {
            mediaFiles.push_back(*sharedFile); // Dereference shared_ptr để lấy MediaFile
        }
    }
    return mediaFiles;
}

// Method to get details of a specific media file by name
MediaFile MediaFileController::getMediaFileDetails(const std::string& name) {
    // Lấy shared_ptr<MediaFile> từ MediaLibrary
    auto sharedMediaFile = modelManager.getMediaLibrary().getMediaFileByName(name);

    // Dereference shared_ptr để trả về MediaFile
    if (sharedMediaFile) {
        return *sharedMediaFile;
    } else {
        //throw std::runtime_error("Media file not found: " + name);
    }
}

void MediaFileController::handleInput() {
    bool isRunning = true;
    while (isRunning) {
        std::cout << "\nMedia Options Menu:\n";
        std::cout << static_cast<int>(MediaMenuOption::ShowAllMediaFiles) << ". Show All Media Files\n";
        std::cout << static_cast<int>(MediaMenuOption::ShowMetadata) << ". Show Metadata\n";
        std::cout << static_cast<int>(MediaMenuOption::BackToMainMenu) << ". Back to Main Menu\n";
        std::cout << "Enter your choice: ";

        int choiceInput;
        std::cin >> choiceInput;
        auto choice = static_cast<MediaMenuOption>(choiceInput);

        switch (choice) {
            case MediaMenuOption::ShowAllMediaFiles: { // Show All Media Files
                auto mediaFiles = getAllMediaFiles();
                auto* mediaFileView = dynamic_cast<ViewMediaFile*>(viewManager.getView("ViewMediaFile"));

                if (mediaFileView) {
                    if (mediaFiles.empty()) {
                        mediaFileView->update("No media files found.");
                    } else {
                        mediaFileView->update("Displaying all media files:");
                        modelManager.getMediaLibrary().getAllMediaFiles();
                        for (const auto& file : mediaFiles) {
                            mediaFileView->update(" - " + file.getName() + " (" + file.getType() + ")");
                        }
                    }
                }
                break;
            }
            case MediaMenuOption::ShowMetadata: { // Show Metadata
                auto* metadataView = dynamic_cast<ViewMetadata*>(viewManager.getView("ViewMetadata"));
                if (metadataView) {
                    std::cout << "Enter the name of the file to view metadata: ";
                    std::string fileName;
                    std::cin >> fileName;

                    try {
                        auto file = getMediaFileDetails(fileName);
                        const auto& metadata = file.getMetadata().getData();
                        if (metadata.empty()) {
                            metadataView->update("No metadata available for this file.");
                        } else {
                            for (const auto& [key, value] : metadata) {
                                metadataView->update(key + ": " + value);
                            }
                        }
                    } catch (const std::exception& e) {
                        metadataView->update("Error: " + std::string(e.what()));
                    }
                }
                break;
            }
            case MediaMenuOption::BackToMainMenu: { // Back to Main Menu
                isRunning = false;
                break;
            }
            default: {
                std::cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    }
}
