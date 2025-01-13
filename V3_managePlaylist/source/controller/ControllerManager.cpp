#include "ControllerManager.hpp"
#include "ViewScanfOption.hpp"
#include "ViewMainMenu.hpp"
#include "ViewMediaFile.hpp"
#include "ViewPlaylist.hpp"
#include "ViewDetailedPlaylist.hpp"
#include "ViewPlay.hpp"
#include "ViewMetadata.hpp"
#include <iostream>
#include <cstdlib>
#include <limits>

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
    // Bước 1: Kiểm tra file media
    scanfOptionController.handleDirectoryScan();
    if (!scanfOptionController.checkMediaFiles()) {
        auto* scanOptionView = dynamic_cast<ViewScanfOption*>(viewManager.getView("ViewScanOption"));
        if (scanOptionView) {
            scanOptionView->update("No media files found. Please add files and try again.");
        }
        return;
    }

    // Bước 2: Hiển thị menu chính
    bool isRunning = true;
    while (isRunning) {
        mainMenuController.showMainMenu();

        int selection;
        std::cin >> selection;

        switch (selection) {
        case 1: { // Hiển thị tất cả file media
            auto mediaFiles = mediaFileController.getAllMediaFiles();
            auto* mediaFileView = dynamic_cast<ViewMediaFile*>(viewManager.getView("ViewMediaFile"));

            if (mediaFileView) {
                if (mediaFiles.empty()) {
                    mediaFileView->update("No media files found.");
                } else {
                    mediaFileView->update("Displaying all media files:");
                    for (const auto& file : mediaFiles) {
                        mediaFileView->update(" - " + file.getName() + " (" + file.getType() + ")");
                    }
                }
            }
            break;
        }
        case 2: { // Hiển thị metadata
            auto* metadataView = dynamic_cast<ViewMetadata*>(viewManager.getView("ViewMetadata"));
            if (metadataView) {
                std::string fileName;
                metadataView->update("Enter the name of the file to view metadata: ");
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                std::getline(std::cin, fileName);

                try {
                    auto file = mediaFileController.getMediaFileDetails(fileName);
                    auto metadata = metadataController.getMediaFileMetadata(file);

                    for (const auto& [key, value] : metadata) {
                        metadataView->update(key + ": " + value);
                    }
                } catch (const std::exception& e) {
                    metadataView->update("Error: " + std::string(e.what()));
                }
            }
            break;
        }
        case 3: {
            auto* playlistView = dynamic_cast<ViewPlaylist*>(viewManager.getView("ViewPlaylist"));
            if (playlistView) {
                bool isManagingPlaylist = true;
                while (isManagingPlaylist) {
                    // Hiển thị menu Playlist
                    std::cout << "\nPlaylist Menu: [1] Create [2] Delete [3] View [4] Add Song [5] Remove Song [0] Exit\n";
                    std::cout << "Enter your choice: ";
                    int playlistMenuOption;
                    std::cin >> playlistMenuOption;

                    switch (playlistMenuOption) {
                        case 1: { // Create Playlist
                            std::cout << "Enter the name of the new playlist: ";
                            std::string playlistName;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                            std::getline(std::cin, playlistName);

                            Playlist newPlaylist(playlistName);
                            try {
                                modelManager.getPlaylistLibrary().addPlaylist(newPlaylist);
                                std::cout << "Playlist '" << playlistName << "' created successfully!\n";
                            } catch (const std::exception& e) {
                                std::cerr << "Error: " << e.what() << "\n";
                            }
                            break;
                        }
                        case 2: { // Delete Playlist
                            std::cout << "Enter the name of the playlist to delete: ";
                            std::string playlistName;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                            std::getline(std::cin, playlistName);

                            try {
                                modelManager.getPlaylistLibrary().removePlaylist(playlistName);
                                std::cout << "Playlist '" << playlistName << "' deleted successfully!\n";
                            } catch (const std::exception& e) {
                                std::cerr << "Error: " << e.what() << "\n";
                            }
                            break;
                        }
                        case 3: { // View Playlists
                            auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
                            if (playlists.empty()) {
                                std::cout << "No playlists available.\n";
                            } else {
                                std::cout << "Playlists:\n";
                                for (const auto& playlist : playlists) {
                                    std::cout << " - " << playlist->getName() << "\n";
                                }

                                std::cout << "\nEnter the name of the playlist to view details: ";
                                std::string playlistName;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                                std::getline(std::cin, playlistName);

                                try {
                                    auto selectedPlaylist = modelManager.getPlaylistLibrary().getPlaylistByName(playlistName);

                                    std::cout << "Songs in playlist '" << playlistName << "':\n";
                                    auto songs = selectedPlaylist->getSongs();
                                    if (songs.empty()) {
                                        std::cout << "No songs in this playlist.\n";
                                    } else {
                                        for (const auto& song : songs) {
                                            std::cout << " - " << song.getName() << " (" << song.getType() << ")\n";
                                        }
                                    }
                                } catch (const std::exception& e) {
                                    std::cerr << "Error: " << e.what() << "\n";
                                }
                            }
                            break;
                        }
                        case 4: { // Add Song to Playlist
                            std::cout << "Enter the name of the playlist to add a song: ";
                            std::string playlistName;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                            std::getline(std::cin, playlistName);

                            try {
                                auto playlist = modelManager.getPlaylistLibrary().getPlaylistByName(playlistName);

                                std::cout << "Enter the name of the song to add: ";
                                std::string songName;
                                std::getline(std::cin, songName);

                                auto mediaFile = modelManager.getMediaLibrary().getMediaFileByName(songName);
                                if (mediaFile) {
                                    playlist->addSong(*mediaFile);
                                    std::cout << "Song '" << songName << "' added to playlist '" << playlistName << "' successfully!\n";
                                } else {
                                    std::cerr << "Error: Song not found in media library.\n";
                                }
                            } catch (const std::exception& e) {
                                std::cerr << "Error: " << e.what() << "\n";
                            }
                            break;
                        }
                        case 5: { // Remove Song from Playlist
                            std::cout << "Enter the name of the playlist to remove a song: ";
                            std::string playlistName;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                            std::getline(std::cin, playlistName);

                            try {
                                auto playlist = modelManager.getPlaylistLibrary().getPlaylistByName(playlistName);

                                std::cout << "Enter the name of the song to remove: ";
                                std::string songName;
                                std::getline(std::cin, songName);

                                auto mediaFile = modelManager.getMediaLibrary().getMediaFileByName(songName);
                                if (mediaFile) {
                                    playlist->removeSong(*mediaFile);
                                    std::cout << "Song '" << songName << "' removed from playlist '" << playlistName << "' successfully!\n";
                                } else {
                                    std::cerr << "Error: Song not found in media library.\n";
                                }
                            } catch (const std::exception& e) {
                                std::cerr << "Error: " << e.what() << "\n";
                            }
                            break;
                        }
                        case 0: { // Exit Playlist Menu
                            isManagingPlaylist = false;
                            break;
                        }
                        default: {
                            std::cout << "Invalid option. Please try again.\n";
                        }
                    }
                }
            } else {
                std::cerr << "Error: Playlist View not found.\n";
            }
            break;
        }
        case 0: { // Thoát chương trình
            auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));
            if (mainMenuView) {
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
}
