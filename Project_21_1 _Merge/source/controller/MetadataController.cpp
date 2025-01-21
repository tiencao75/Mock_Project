#include "MetadataController.hpp"
#include "ExceptionLib.hpp"
#include <iostream>
#include <iomanip> // Để sử dụng std::setw và std::left
#include <limits>

// Constructor
MetadataController::MetadataController(ModelManager &modelManager, ViewManager &viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

// Destructor
MetadataController::~MetadataController() {}

// Method to get metadata of a media file
std::map<std::string, std::string> MetadataController::getMediaFileMetadata(MediaFile &file)
{
    return file.getMetadata().getData();
}

void MetadataController::updateMediaFileMetadata(MediaFile &file, const std::string &key, const std::string &value)
{
    // Lấy metadata hiện tại
    auto metadata = file.getMetadata().getData();
    metadata[key] = value; // Cập nhật giá trị mới
    Metadata updatedMetadata;
    updatedMetadata.setData(metadata); // Gán dữ liệu mới vào metadata
    file.setMetadata(updatedMetadata); // Cập nhật metadata vào file
}
void MetadataController::handleInput()
{
    viewManager.getCurrentView()->hide();
    auto *metadataView = dynamic_cast<ViewMetadata *>(viewManager.getView("ViewMetadata"));
    if (!metadataView)
    {
        throw ViewNotFoundException("ViewMetadata not found.");
    }

    // Hiển thị danh sách các tệp media
    const auto &mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
    if (mediaFiles.empty())
    {
        metadataView->update("No media files available.");
        viewManager.getCurrentView()->pauseScreen();
        return;
    }

    viewManager.getCurrentView()->hide();
    metadataView->update("=== Available Media Files ===");
    // for (const auto &[id, mediaFile] : mediaFiles)
    // {
    //     metadataView->update(std::to_string(id) + ": " + mediaFile->getName());
    // }
    modelManager.getMediaLibrary().displayPaginatedFiles(mediaFiles);

    size_t fileID;
    Exception_Handler("Enter the ID of the media file to edit metadata: ", fileID, validateID);

    auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
    if (!mediaFile)
    {
        throw MediaFileNotFoundException("Media file with the provided ID does not exist.");
    }

    auto currentMetadata = getMediaFileMetadata(*mediaFile);
    const auto originalMetadata = currentMetadata;

    size_t choice;
    do
    {
        // Hiển thị metadata hiện tại
        metadataView->update("\n=== Current Metadata ===");

        for (const auto &[key, value] : currentMetadata) {
            std::cout << std::setw(20) << std::left // Key canh lề trái, độ dài tối đa 20 ký tự
                    << key 
                    << ": " 
                    << (value.empty() ? "unknown" : value) // Giá trị hiển thị "unknown" nếu rỗng
                    << "\n";
        }


        // Hiển thị menu chỉnh sửa
        // metadataView->update("\nChoose an option to edit metadata:");
        // metadataView->update("1. Edit Title");
        // metadataView->update("2. Edit Artist");
        // metadataView->update("3. Edit Album");
        // metadataView->update("4. Edit Genre");
        // metadataView->update("5. Edit Year");
        // metadataView->update("6. Edit Track");
        // metadataView->update("7. Restore Original Values");
        // metadataView->update("0. Exit Editing");
        viewManager.getCurrentView()->hide();
        viewManager.getView("ViewMetadata")->show();

        Exception_Handler("Enter your choice: ", choice, validateEditAudioMenu);

        std::string newValue;
        switch (choice)
        {
        case 1:
            Exception_Handler("Enter new title: ", newValue, validateAlphaSring);
            currentMetadata["Title"] = newValue;
            viewManager.getCurrentView()->pauseScreen();
            break;
        case 2:
            Exception_Handler("Enter new artist: ", newValue, validateAlphaSring);
            currentMetadata["Artist"] = newValue;
            viewManager.getCurrentView()->pauseScreen();
            break;
        case 3:
            Exception_Handler("Enter new album: ", newValue, validateAlphaSring);
            currentMetadata["Album"] = newValue;
            viewManager.getCurrentView()->pauseScreen();
            break;
        case 4:
            Exception_Handler("Enter new genre: ", newValue, validateAlphaSring);
            currentMetadata["Genre"] = newValue;
            viewManager.getCurrentView()->pauseScreen();
            break;
        case 5:
            Exception_Handler("Enter new year: ", newValue, validateYear);
            currentMetadata["Year"] = newValue;
            viewManager.getCurrentView()->pauseScreen();
            break;
        case 6:
            Exception_Handler("Enter new track: ", newValue, validateTrack);
            currentMetadata["Track"] = newValue;
            viewManager.getCurrentView()->pauseScreen();
            break;
        case 7:
            metadataView->update("Restoring original values...");
            for (const auto &[key, value] : originalMetadata)
            {
                updateMediaFileMetadata(*mediaFile, key, value);
            }
            metadataView->update("Original metadata restored successfully.");
            currentMetadata = originalMetadata;
            viewManager.getCurrentView()->pauseScreen();
            break;
        case 0:
            metadataView->update("Exiting editing...");
            viewManager.getCurrentView()->pauseScreen();
            break;
        default:
            metadataView->update("Invalid choice, please try again.");
            viewManager.getCurrentView()->pauseScreen();
        }

        // Cập nhật metadata nếu có thay đổi
        if (choice != 0 && choice != 7)
        {
            for (const auto &[key, value] : currentMetadata)
            {
                updateMediaFileMetadata(*mediaFile, key, value);
            }
            metadataView->update("Metadata updated successfully.");
        }
    } while (choice != 0);
}
