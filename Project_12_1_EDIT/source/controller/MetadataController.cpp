#include "MetadataController.hpp"
#include <iostream>
#include <limits>

// Constructor
MetadataController::MetadataController(ModelManager& modelManager, ViewManager& viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

// Destructor
MetadataController::~MetadataController() {}

// Method to get metadata of a media file
std::map<std::string, std::string> MetadataController::getMediaFileMetadata(MediaFile& file) {
    return file.getMetadata().getData();
}

void MetadataController::updateMediaFileMetadata(MediaFile& file, const std::string& key, const std::string& value) {
    // Lấy metadata hiện tại
    auto metadata = file.getMetadata().getData();
    metadata[key] = value; // Cập nhật giá trị mới
    Metadata updatedMetadata;
    updatedMetadata.setData(metadata); // Gán dữ liệu mới vào metadata
    file.setMetadata(updatedMetadata); // Cập nhật metadata vào file
}
void MetadataController::handleInput() {
    auto* metadataView = dynamic_cast<ViewMetadata*>(viewManager.getView("ViewMetadata"));
    if (!metadataView) {
        throw std::runtime_error("ViewMetadata not found.");
    }

    // Hiển thị danh sách các tệp media
    const auto& mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
    if (mediaFiles.empty()) {
        metadataView->update("No media files available.");
        return;
    }

    metadataView->update("=== Available Media Files ===");
    for (const auto& [id, mediaFile] : mediaFiles) {
        metadataView->update(std::to_string(id) + ": " + mediaFile->getName());
    }

    // Yêu cầu người dùng chọn tệp bằng ID
    metadataView->update("Enter the ID of the media file to edit metadata: ");
    unsigned int fileID;
    std::cin >> fileID;
    if (std::cin.fail()) {
        metadataView->update("Invalid input. Please enter a valid number.");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
    if (!mediaFile) {
        metadataView->update("Media file not found.");
        return;
    }

    // Lấy metadata hiện tại
    std::map<std::string, std::string> currentMetadata = getMediaFileMetadata(*mediaFile);
    const std::map<std::string, std::string> originalMetadata = currentMetadata;

    int choice;
    do {
        // Hiển thị metadata hiện tại
        metadataView->update("\n=== Current Metadata ===");
        for (const auto& [key, value] : currentMetadata) {
            metadataView->update(key + ": " + value);
        }

        // Hiển thị menu chỉnh sửa
        metadataView->update("\nChoose an option to edit metadata:");
        metadataView->update("1. Edit Title");
        metadataView->update("2. Edit Artist");
        metadataView->update("3. Edit Album");
        metadataView->update("4. Edit Genre");
        metadataView->update("5. Edit Year");
        metadataView->update("6. Edit Track");
        metadataView->update("7. Restore Original Values");
        metadataView->update("0. Exit Editing");
        metadataView->update("Enter your choice: ");

        std::cin >> choice;
        if (std::cin.fail()) {
            metadataView->update("Invalid input. Please enter a number.");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

        std::string newValue;
        switch (choice) {
            case 1:
                metadataView->update("Enter new title: ");
                std::getline(std::cin, newValue);
                currentMetadata["Title"] = newValue;
                break;
            case 2:
                metadataView->update("Enter new artist: ");
                std::getline(std::cin, newValue);
                currentMetadata["Artist"] = newValue;
                break;
            case 3:
                metadataView->update("Enter new album: ");
                std::getline(std::cin, newValue);
                currentMetadata["Album"] = newValue;
                break;
            case 4:
                metadataView->update("Enter new genre: ");
                std::getline(std::cin, newValue);
                currentMetadata["Genre"] = newValue;
                break;
            case 5:
                metadataView->update("Enter new year: ");
                std::getline(std::cin, newValue);
                currentMetadata["Year"] = newValue;
                break;
            case 6:
                metadataView->update("Enter new track: ");
                std::getline(std::cin, newValue);
                currentMetadata["Track"] = newValue;
                break;
            case 7:
                metadataView->update("Restoring original values...");
                for (const auto& [key, value] : originalMetadata) {
                    updateMediaFileMetadata(*mediaFile, key, value);
                }
                metadataView->update("Original metadata restored successfully.");
                currentMetadata = originalMetadata;
                break;
            case 0:
                metadataView->update("Exiting editing...");
                break;
            default:
                metadataView->update("Invalid choice, please try again.");
        }

        // Cập nhật metadata nếu có thay đổi
        if (choice != 0 && choice != 7) {
            for (const auto& [key, value] : currentMetadata) {
                updateMediaFileMetadata(*mediaFile, key, value);
            }
            metadataView->update("Metadata updated successfully.");
        }
    } while (choice != 0);
}


            
        
