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
      metadataController(modelManager, viewManager) {
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
ModelManager& ControllerManager::getModelManager() {
    return modelManager;
}

// Getter cho ViewManager
ViewManager& ControllerManager::getViewManager() {
    return viewManager;
}
// Hàm xử lý dữ liệu từ người dùng
void ControllerManager::handleInputData() {
    // Bước 1: Kiểm tra file media qua ScanfOptionController
    auto* scanOptionView = dynamic_cast<ViewScanfOption*>(viewManager.getView("ViewScanOption"));
    if (scanOptionView) {
        scanOptionView->update("Checking for media files...");
    }

    scanfOptionController.handleDirectoryScan();
    bool mediaFilesExist = scanfOptionController.checkMediaFiles();
    if (!mediaFilesExist) {
        if (scanOptionView) {
            scanOptionView->update("No media files found. Please add files and try again.");
        }
        return; // Dừng lại nếu không có file
    }

    // Bước 2: Hiển thị menu chính qua MainMenuController
    bool isRunning = true;
    while (isRunning) {
        mainMenuController.showMainMenu(); // Hiển thị Main Menu qua View

        // Lựa chọn từ người dùng
        int selection;
        std::cin >> selection;

        // Điều hướng logic dựa trên lựa chọn
        switch (selection) {
        case 1:
            mediaFileController.getAllMediaFiles();
            break;
        case 2:
            //metadataController.getMediaFileMetadata();
            break;
        case 0:
            if (auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"))) {
                mainMenuView->update("Exiting application...");
            }
            isRunning = false;
            break;
        default:
            if (auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"))) {
                mainMenuView->update("Invalid option. Please try again.");
            }
            break;
        }
    }
}
