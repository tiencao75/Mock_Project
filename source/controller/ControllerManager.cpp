#include "ControllerManager.hpp"
#include "PlayingMediaController.hpp"
#include "ViewScanfOption.hpp"
#include "ViewMainMenu.hpp"
#include "ViewMediaFile.hpp"
#include "ViewPlaylist.hpp"
#include "ViewDetailedPlaylist.hpp"
#include "ViewPlay.hpp"
#include "ViewMetadata.hpp"
#include "ExceptionLib.hpp"
#include "PlayingMediaController.hpp"
#include "S32K144Interface.hpp"
#include <fstream>
#include <iostream>
#include <mutex>

ControllerManager::ControllerManager()
    : scanfOptionController(modelManager, viewManager),
      mainMenuController(modelManager, viewManager),
      mediaFileController(modelManager, viewManager),
      metadataController(modelManager, viewManager), 
      playingMediaController(modelManager, viewManager),
      playlistController(modelManager, viewManager){
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

PlayingMediaController& ControllerManager::getPlayingMediaController() {
    return playingMediaController;
}

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

void ControllerManager::readPlaylistsFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error: Unable to open file " << filename << " for reading.\n";
        return;
    }

    std::map<unsigned int, std::shared_ptr<Playlist>> playlists;
    std::string line;
    std::shared_ptr<Playlist> currentPlaylist = nullptr;
    unsigned int playlistIndex = 1;

    while (std::getline(inFile, line)) {
        try {
            if (line.rfind("Playlist: ", 0) == 0) { // Bắt đầu một playlist mới
                std::string playlistName = line.substr(10);
                currentPlaylist = std::make_shared<Playlist>(playlistName);
                playlists[playlistIndex++] = currentPlaylist;
            } else if (line == "---") { // Dấu phân cách playlist
                currentPlaylist = nullptr;
            } else if (currentPlaylist && !line.empty()) { // Đọc bài hát
                std::istringstream ss(line);
                unsigned int songID;
                std::string songPath, songType;

                if (std::getline(ss, line, ',') && std::stringstream(line) >> songID &&
                    std::getline(ss, songPath, ',') &&
                    std::getline(ss, songType)) {
                    MediaFile song(songPath.substr(songPath.find_last_of("/") + 1), songPath, songType);
                    currentPlaylist->addSong(songID, song);
                } else {
                    std::cerr << "Warning: Invalid song format in line: " << line << "\n";
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << "\n";
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }

    inFile.close();

    // Cập nhật danh sách playlist
    modelManager.getPlaylistLibrary().setPlaylists(playlists);
    std::cout << "Playlists loaded from file: " << filename << "\n";
}

void ControllerManager::handleInputData() {
    const std::string filename = "playlistsData.txt";
    try {
        readPlaylistsFromFile(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    try {
        // Step 1: Call handleInput in ScanfOptionController
        scanfOptionController.handleInput();
        auto& s32kInterface = S32K144Interface::getInstance(playingMediaController);
        s32kInterface.startReadingSignal();

        // Step 2: Display main menu
        bool isRunning = true;
        while (isRunning) {
            // viewManager.getCurrentView()->pauseScreen();
            viewManager.getCurrentView()->hide();

            // Display Main Menu
            mainMenuController.showMainMenu();
            // Read user input and validate
            size_t selectionInput;
            Exception_Handler("Enter main menu choice: ", selectionInput, validateMainMenu);

            auto selection = static_cast<MainMenuOption>(selectionInput);

            switch (selection) {
                case MainMenuOption::SacanfOption: {
                    try {
                        scanfOptionController.handleInput();
                    } catch (const std::exception& e) {
                        std::cerr << "Error handling ScanfOption: " << e.what() << std::endl;
                    }
                    break;
                }
                case MainMenuOption::MediaFiledData: {
                    try {
                        mediaFileController.handleInput();
                    } catch (const std::exception& e) {
                        std::cerr << "Error handling MediaFileData: " << e.what() << std::endl;
                    }
                    break;
                }
                case MainMenuOption::EditMetadata: {
                    try {
                        metadataController.handleInput();
                    } catch (const std::exception& e) {
                        std::cerr << "Error handling EditMetadata: " << e.what() << std::endl;
                    }
                    break;
                }
                case MainMenuOption::ManagerPlayList: {
                    try {
                        playlistController.handleInput();
                    } catch (const std::exception& e) {
                        std::cerr << "Error handling PlaylistManager: " << e.what() << std::endl;
                    }
                    break;
                }
                case MainMenuOption::PlayingMedia: {
                    try {
                        
                        playingMediaController.handleInput();
                    } catch (const std::exception& e) {
                        std::cerr << "Error handling PlayingMedia: " << e.what() << std::endl;
                    }
                    break;
                }
                case MainMenuOption::Exit: {
                    auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));
                    if (mainMenuView) {
                        s32kInterface.stopReadingSignal();
                        mainMenuView->update("Exiting application...");
                    }
                    isRunning = false;
                    break;
                }
                default: {
                    auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));
                    if (mainMenuView) {
                        mainMenuView->update("Invalid option. Please try again.");
                    }
                    break;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Critical error in handleInputData: " << e.what() << std::endl;
    }
}
