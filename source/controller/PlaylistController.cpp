#include "PlaylistController.hpp"
#include <iostream>
#include <limits>

// Constructor
PlaylistController::PlaylistController(ModelManager& modelManager, ViewManager& viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

// Destructor
PlaylistController::~PlaylistController() {}

// Method to get all playlists
std::vector<std::shared_ptr<Playlist>> PlaylistController::getAllPlaylists() {
    return modelManager.getPlaylistLibrary().getAllPlaylists();
}

// Method to create a new playlist with the given name
void PlaylistController::createPlaylist(const std::string& name) {
    try {
        Playlist newPlaylist(name);
        modelManager.getPlaylistLibrary().addPlaylist(newPlaylist);
        std::cout << "Playlist '" << name << "' created successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

// Method to delete a playlist by its name
void PlaylistController::deletePlaylist(const std::string& name) {
    try {
        modelManager.getPlaylistLibrary().removePlaylist(name);
        std::cout << "Playlist '" << name << "' deleted successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

// Method to handle user input for managing playlists
void PlaylistController::handleInput() {
    bool isManagingPlaylist = true;

    while (isManagingPlaylist) {
        std::cout << "\n=== Playlist Menu ===\n";
        std::cout << "[1] Create Playlist\n";
        std::cout << "[2] Delete Playlist\n";
        std::cout << "[3] View All Playlists\n";
        std::cout << "[4] Add Song to Playlist\n";
        std::cout << "[5] Remove Song from Playlist\n";
        std::cout << "[6] View Songs in a Playlist\n";
        std::cout << "[0] Exit Playlist Menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

        switch (choice) {
            case 1: { // Create Playlist
                std::cout << "Enter the name of the new playlist: ";
                std::string playlistName;
                std::getline(std::cin, playlistName);
                createPlaylist(playlistName);
                break;
            }

            case 2: { // Delete Playlist
                std::cout << "Enter the name of the playlist to delete: ";
                std::string playlistName;
                std::getline(std::cin, playlistName);
                deletePlaylist(playlistName);
                break;
            }

            case 3: { // View All Playlists
                auto playlists = getAllPlaylists();
                if (playlists.empty()) {
                    std::cout << "No playlists available.\n";
                } else {
                    std::cout << "Available Playlists:\n";
                    for (const auto& playlist : playlists) {
                        std::cout << " - " << playlist->getName() << "\n";
                    }
                }
                break;
            }

            case 4: { // Add Song to Playlist
                std::cout << "Enter the name of the playlist to add a song: ";
                std::string playlistName;
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

            case 6: { // View Songs in a Playlist
                std::cout << "Enter the name of the playlist to view songs: ";
                std::string playlistName;
                std::getline(std::cin, playlistName);

                try {
                    auto playlist = modelManager.getPlaylistLibrary().getPlaylistByName(playlistName);

                    std::cout << "Songs in playlist '" << playlistName << "':\n";
                    auto songs = playlist->getSongs();
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
                break;
            }

            case 0: // Exit Playlist Menu
                isManagingPlaylist = false;
                break;

            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}