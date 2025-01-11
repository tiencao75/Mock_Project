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
#include <fstream>
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

// Hàm đọc dữ liệu từ file
std::map<std::string, std::string> ControllerManager::readDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::map<std::string, std::string> data;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue; // Bỏ qua dòng trống hoặc comment
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                data[key] = value;
            }
        }
        file.close();
    }

    return data;
}

// Hàm ghi dữ liệu vào file
void ControllerManager::writeDataToFile(const std::string& filename, const std::map<std::string, std::string>& data) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const auto& [key, value] : data) {
            file << key << "=" << value << "\n";
        }
        file.close();
    }
}
// Hàm xử lý dữ liệu từ người dùng
// void ControllerManager::handleInputData() {
//     // Bước 1: Kiểm tra file media
//     scanfOptionController.handleDirectoryScan();
//     if (0) { //!scanfOptionController.checkMediaFiles()
//         auto* scanOptionView = dynamic_cast<ViewScanfOption*>(viewManager.getView("ViewScanOption"));
//         if (scanOptionView) {
//             scanOptionView->update("No media files found. Please add files and try again.");
//         }
//         return;
//     }

//     // Bước 2: Hiển thị menu chính
//     bool isRunning = true;
//     while (isRunning) {
//         mainMenuController.showMainMenu();

//         int selection;
//         std::cin >> selection;

//         switch (selection) {
//         case 1: { // Hiển thị tất cả file media
//         // Lấy danh sách file từ MediaLibrary thông qua ModelManager
//         const auto& mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
//         auto* mediaFileView = dynamic_cast<ViewMediaFile*>(viewManager.getView("ViewMediaFile"));

//         if (mediaFileView) {
//             if (mediaFiles.empty()) {
//                 mediaFileView->update("No media files found.");
//             } else {
//                 mediaFileView->update("Displaying all media files:");
//                 for (const auto& file : mediaFiles) {
//                     if (file) { // Kiểm tra null pointer
//                         mediaFileView->update(" - " + file->getName() + " (" + file->getType() + ")");
//                     }
//                 }
//             }
//         }
//         break;
//         }

//         case 2: { // Hiển thị metadata
//         auto* metadataView = dynamic_cast<ViewMetadata*>(viewManager.getView("ViewMetadata"));
        
//         if (metadataView) {
//             std::string fileName;
//             metadataView->update("Enter the name of the file to view metadata: ");
//             std::cin >> fileName;

//             try {
//                 // Lấy file từ MediaLibrary
//                 auto file = modelManager.getMediaLibrary().getMediaFileByName(fileName);
//                 if (!file) {
//                     throw std::runtime_error("File not found: " + fileName);
//                 }

//                 // Lấy metadata từ file và hiển thị
//                 const auto& metadata = file->getMetadata().getData();
//                 if (metadata.empty()) {
//                     metadataView->update("No metadata available for this file.");
//                 } else {
//                     for (const auto& [key, value] : metadata) {
//                         metadataView->update(key + ": " + value);
//                     }
//                 }
//             } catch (const std::exception& e) {
//                 metadataView->update("Error: " + std::string(e.what()));
//             }
//         }
//         break;
//         }
//         case 3: { //Edit metadataFile
//         metadataController.handleInput();
//         }
//         case 0: { // Thoát chương trình
//             auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));
//             if (mainMenuView) {
//                 mainMenuView->update("Exiting application...");
//             }
//             isRunning = false;
//             break;
//         }
//         default: {
//             auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));
//             if (mainMenuView) {
//                 mainMenuView->update("Invalid option. Please try again.");
//             }
//             break;
//         }
//         }
//     }
// }

void ControllerManager::handleInputData() {
    // Bước 1: Gọi hàm handleInput trong ScanfOptionController
    scanfOptionController.handleInput();

    // Bước 2: Hiển thị menu chính
    bool isRunning = true;
    while (isRunning) {
        // Hiển thị Main Menu
        mainMenuController.showMainMenu();

        // Đọc lựa chọn của người dùng
        int selectionInput;
        std::cin >> selectionInput;
        auto selection = static_cast<MainMenuOption>(selectionInput);

        switch (selection) {
            case MainMenuOption::ShowAllMediaFiles: { // Hiển thị tất cả file media
            // Lấy danh sách file từ MediaLibrary thông qua ModelManager
            const auto& mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
            auto* mediaFileView = dynamic_cast<ViewMediaFile*>(viewManager.getView("ViewMediaFile"));

            if (mediaFileView) {
                if (mediaFiles.empty()) {
                    mediaFileView->update("No media files found.");
                } else {
                    mediaFileView->update("Displaying all media files:");
                    for (const auto& file : mediaFiles) {
                        if (file) { // Kiểm tra null pointer
                            mediaFileView->update(" - " + file->getName() + " (" + file->getType() + ")");
                        }
                    }
                }
            }
            break;
            }

            case MainMenuOption::ShowMetadata: { // Hiển thị metadata của một file
                auto* metadataView = dynamic_cast<ViewMetadata*>(viewManager.getView("ViewMetadata"));

                if (metadataView) {
                    std::string fileName;
                    metadataView->update("Enter the name of the file to view metadata: ");
                    std::cin >> fileName;

                    try {
                        auto file = modelManager.getMediaLibrary().getMediaFileByName(fileName);
                        if (!file) {
                            throw std::runtime_error("File not found: " + fileName);
                        }

                        const auto& metadata = file->getMetadata().getData();
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

            case MainMenuOption::EditMetadata: { // Sửa metadata
                metadataController.handleInput();
                break;
            }

            case MainMenuOption::Exit: { // Thoát chương trình
                auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));
                if (mainMenuView) {
                    mainMenuView->update("Exiting application...");
                }
                isRunning = false;
                break;
            }

            default: { // Lựa chọn không hợp lệ
                auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));
                if (mainMenuView) {
                    mainMenuView->update("Invalid option. Please try again.");
                }
                break;
            }
        }
    }
}

