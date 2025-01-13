#include "ControllerManager.hpp"
#include "PlayingMediaController.hpp"
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
      metadataController(modelManager, viewManager),
      playingMediaController(modelManager, viewManager),
      playlistController(modelManager, viewManager)  // Pass required arguments
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

// Getter for ModelManager
ModelManager& ControllerManager::getModelManager() {
    return modelManager;
}

// Getter for ViewManager
ViewManager& ControllerManager::getViewManager() {
    return viewManager;
}

// Read data from file
std::map<std::string, std::string> ControllerManager::readDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::map<std::string, std::string> data;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue; // Skip empty or comment lines
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

// Write data to file
void ControllerManager::writeDataToFile(const std::string& filename, const std::map<std::string, std::string>& data) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const auto& [key, value] : data) {
            file << key << "=" << value << "\n";
        }
        file.close();
    }
}

// Handle input data and direct logic
void ControllerManager::handleInputData() {
    // Step 1: Call handleInput in ScanfOptionController
    scanfOptionController.handleInput();

    // Step 2: Display main menu
    bool isRunning = true;
    while (isRunning) {
        // Display Main Menu
        mainMenuController.showMainMenu();

        // Read user choice
        int selectionInput;
        std::cin >> selectionInput;
        auto selection = static_cast<MainMenuOption>(selectionInput);

        switch (selection) {
            case MainMenuOption::ShowAllMediaFiles: { // Show all media files
                const auto& mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
                auto* mediaFileView = dynamic_cast<ViewMediaFile*>(viewManager.getView("ViewMediaFile"));

                if (mediaFileView) {
                    if (mediaFiles.empty()) {
                        mediaFileView->update("No media files found.");
                    } else {
                        mediaFileView->update("Displaying all media files:");
                        for (const auto& file : mediaFiles) {
                            if (file) { // Check for null pointers
                                mediaFileView->update(" - " + file->getName() + " (" + file->getType() + ")");
                            }
                        }
                    }
                }
                break;
            }

            case MainMenuOption::ShowMetadata: { // Show metadata of a file
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

            case MainMenuOption::EditMetadata: { // Edit metadata
                metadataController.handleInput();
                break;
            }

            case MainMenuOption::ManagerPlayList: { // Manage playlists
                playlistController.handleInput(); // Delegate to PlaylistController
                break;
            }

            case MainMenuOption::PlayingMedia: { // Handle playing media
                playingMediaController.handleInput();
                break;
            }

            case MainMenuOption::Exit: { // Exit the application
                auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));
                if (mainMenuView) {
                    mainMenuView->update("Exiting application...");
                }
                isRunning = false;
                break;
            }

            default: { // Invalid option
                auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));
                if (mainMenuView) {
                    mainMenuView->update("Invalid option. Please try again.");
                }
                break;
            }
        }
    }
}
