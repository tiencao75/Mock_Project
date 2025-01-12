// #include "ControllerManager.hpp"
// #include <iostream>

// // Constructor
// ControllerManager::ControllerManager()
//     : scanfOptionController(modelManager, viewManager),
//       mainMenuController(modelManager, viewManager) {}

// // Destructor
// ControllerManager::~ControllerManager() {}

// void ControllerManager::handleInputData() {
//     // Kiểm tra file media qua ScanfOptionController
//     scanfOptionController.handleDirectoryScan();

//     // Hiển thị Main Menu
//     mainMenuController.showMainMenu();
// }
#include "ControllerManager.hpp"
#include "ViewScanfOption.hpp"
#include "ViewMainMenu.hpp"
#include "ViewMediaFile.hpp"
#include "ViewPlaylist.hpp"
#include "ViewDetailedPlaylist.hpp"
#include "ViewPlay.hpp"
#include "ViewMetadata.hpp"
#include <iostream>

ControllerManager::ControllerManager()
    : scanfOptionController(modelManager, viewManager),
      mainMenuController(modelManager, viewManager),
      mediaFileController(modelManager, viewManager),
      metadataController(modelManager, viewManager)
{
    viewManager.addView(std::make_unique<ViewScanfOption>());
    viewManager.addView(std::make_unique<ViewMainMenu>());
    viewManager.addView(std::make_unique<ViewMediaFile>());
    viewManager.addView(std::make_unique<ViewPlaylist>());
    viewManager.addView(std::make_unique<ViewDetailedPlaylist>());
    viewManager.addView(std::make_unique<ViewPlay>());
    viewManager.addView(std::make_unique<ViewMetadata>());
}

// Destructor
ControllerManager::~ControllerManager() {}
// Getter cho ModelManager
ModelManager &ControllerManager::getModelManager()
{
    return modelManager;
}

// Getter cho ViewManager
ViewManager &ControllerManager::getViewManager()
{
    return viewManager;
}
// Hàm xử lý dữ liệu từ người dùng
void ControllerManager::handleInputData()
{
    // Bước 1: Kiểm tra file media
    scanfOptionController.handleDirectoryScan();
    if (!scanfOptionController.checkMediaFiles())
    {
        auto *scanOptionView = dynamic_cast<ViewScanfOption *>(viewManager.getView("ViewScanOption"));
        if (scanOptionView)
        {
            scanOptionView->update("No media files found. Please add files and try again.");
        }
        return;
    }

    // Bước 2: Hiển thị menu chính
    bool isRunning = true;
    while (isRunning)
    {
        mainMenuController.showMainMenu();

        int selection;
        std::cin >> selection;

        switch (selection)
        {
        case 1:
        { // Hiển thị tất cả file media
            auto mediaFiles = mediaFileController.getAllMediaFiles();
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
                    for (const auto &file : mediaFiles)
                    {
                        mediaFileView->update(" - " + file.getName() + " (" + file.getType() + ")");
                    }
                }
            }
            break;
        }
        case 2:
        { // Quét USB
            auto *scanOptionView = dynamic_cast<ViewScanfOption *>(viewManager.getView("ViewScanfOption"));
            if (scanOptionView)
            {
                scanOptionView->showScanMenu();
                scanfOptionController.handleUSBScan();
            }
            break;
        }
        case 3:
        { // Hiển thị metadata
            auto *metadataView = dynamic_cast<ViewMetadata *>(viewManager.getView("ViewMetadata"));
            if (metadataView)
            {
                std::string fileName;
                metadataView->update("Enter the name of the file to view metadata: ");
                std::cin >> fileName;

                try
                {
                    auto file = mediaFileController.getMediaFileDetails(fileName);
                    auto metadata = metadataController.getMediaFileMetadata(file);

                    for (const auto &[key, value] : metadata)
                    {
                        metadataView->update(key + ": " + value);
                    }
                }
                catch (const std::exception &e)
                {
                    metadataView->update("Error: " + std::string(e.what()));
                }
            }
            break;
        }
        case 0:
        { // Thoát chương trình
            auto *mainMenuView = dynamic_cast<ViewMainMenu *>(viewManager.getView("ViewMainMenu"));
            if (mainMenuView)
            {
                mainMenuView->update("Exiting application...");
            }
            isRunning = false;
            break;
        }
        default:
        {
            auto *mainMenuView = dynamic_cast<ViewMainMenu *>(viewManager.getView("ViewMainMenu"));
            if (mainMenuView)
            {
                mainMenuView->update("Invalid option. Please try again.");
            }
            break;
        }
        }
    }
}
