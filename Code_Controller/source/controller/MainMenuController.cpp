#include "MainMenuController.hpp"
#include "ScanfOptionController.hpp"
#include "PlaylistController.hpp"
#include "MediaFileController.hpp"
#include <iostream>

// Constructor
MainMenuController::MainMenuController(ControllerManager* manager)
    : controllerManager(manager) {
    // Initialize MainMenuController with the ControllerManager
}

// Destructor
MainMenuController::~MainMenuController() {
    // Clean up resources if needed (no special resources to clean in this case)
}

// Display the main menu
void MainMenuController::showMainMenu() {
    std::cout << "======= Main Menu =======" << std::endl;
    std::cout << "1. Scan Directory" << std::endl;
    std::cout << "2. View Playlist" << std::endl;
    std::cout << "3. Manage Media Files" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

// Handle the user's menu selection
void MainMenuController::handleMenuSelection(int option) {
    switch (option) {
        case 1:
            size_t selection;
            controllerManager->getScanfOptionController()->showScanOptions();
            std::cin>>selection;
            if(selection==1){
                std::string path;
                std::cout<<"Enter path to scan:";
                std::cin>>path;
                controllerManager->getScanfOptionController()->processDirectoryInput(path);
            }
            if(selection==2){
                controllerManager->getScanfOptionController()->processUSBScan();
            }
            break;
        case 2:
            std::cout << "Viewing Playlist..." << std::endl;
            // Call method to view the playlist
            controllerManager->getPlaylistController()->getAllPlaylists();
            break;
        case 3:
            std::cout << "Managing Media Files..." << std::endl;
            // Call method to manage media files (e.g., view media files)
            controllerManager->getMediaFileController()->getAllMediaFiles();
            break;
        case 4:
            std::cout << "Exiting program." << std::endl;
            exit(0); // Exit the program
            break;
        default:
            std::cout << "Invalid selection! Please choose again." << std::endl;
    }
}
