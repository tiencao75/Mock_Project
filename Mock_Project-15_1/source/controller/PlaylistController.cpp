#include "PlaylistController.hpp"
#include "ControllerManager.hpp"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <map>
#include <string>


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


void PlaylistController::handleInput() {
    const std::string filename = "playlistsData.txt";

    // Read existing playlist data from file
    auto data = ControllerManager::readDataFromFile(filename);

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

                // Update data and save to file
                data[playlistName] = ""; // Empty string for no songs initially
                std::cout << "Saving playlist data...\n";
                writeDataToFileFormatted(filename, data);
                std::cout << "Playlist data saved successfully.\n";
                break;
            }

            case 2: { // Delete Playlist
                std::cout << "Enter the name of the playlist to delete: ";
                std::string playlistName;
                std::getline(std::cin, playlistName);
                deletePlaylist(playlistName);

                // Remove from data and save to file
                data.erase(playlistName);
                std::cout << "Saving playlist data...\n";
                writeDataToFileFormatted(filename, data);
                std::cout << "Playlist data saved successfully.\n";
                break;
            }

            case 3: { // View All Playlists
                std::ifstream inFile(filename);
                if (!inFile) {
                    std::cerr << "Error: Unable to open file " << filename << " for reading.\n";
                    break;
                }

                std::cout << "\n=== Playlists in File ===\n";
                std::string line;
                while (std::getline(inFile, line)) {
                    std::cout << line << "\n";
                }
                inFile.close();
                break;
            }

            case 4: { // Add Song to Playlist
                 try
                        {
                            // Hiển thị danh sách playlist hiện có
                            auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
                            if (playlists.empty())
                            {
                                std::cout << "No playlists available. Please create a playlist first.\n";
                                break;
                            }

                            // Hiển thị danh sách playlist
                            std::cout << "Available Playlists:\n";
                            for (size_t i = 0; i < playlists.size(); ++i)
                            {
                                std::cout << i + 1 << ": " << playlists[i]->getName() << "\n";
                            }

                            // Yêu cầu chọn playlist
                            std::cout << "Enter the number of the playlist to add a song to: ";
                            int playlistIndex;
                            std::cin >> playlistIndex;

                            // Kiểm tra lựa chọn hợp lệ
                            if (playlistIndex < 1 || playlistIndex > playlists.size())
                            {
                                std::cerr << "Invalid playlist selection.\n";
                                break;
                            }
                            auto selectedPlaylist = playlists[playlistIndex - 1];

                            // Hiển thị danh sách media files
                            const auto &mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
                            if (mediaFiles.empty())
                            {
                                std::cout << "No media files available to add.\n";
                                break;
                            }

                            std::cout << "Available Media Files (ID: Name):\n";
                            for (const auto &[id, file] : mediaFiles)
                            {
                                std::cout << id << ": " << file->getName() << "\n";
                            }

                            // Yêu cầu chọn bài hát theo ID
                            std::cout << "Enter the ID of the song to add: ";
                            unsigned int fileID;
                            std::cin >> fileID;

                            // Lấy bài hát từ ID
                            auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
                            if (!mediaFile)
                            {
                                std::cerr << "Error: File with the provided ID does not exist.\n";
                                break;
                            }

                            // Thêm bài hát vào playlist
                            selectedPlaylist->addSong(*mediaFile);
                            std::cout << "Song '" << mediaFile->getName() << "' added to playlist '" << selectedPlaylist->getName() << "' successfully!\n";
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << "An error occurred while adding the song to the playlist: " << e.what() << "\n";
                        }
                        catch (...)
                        {
                            std::cerr << "An unknown error occurred while adding the song to the playlist.\n";
                        }
                        break;
            }

            case 5: { // Remove Song from Playlist
                 try
                        {
                            // Lấy danh sách playlist
                            auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
                            if (playlists.empty())
                            {
                                std::cout << "No playlists available. Please create a playlist first.\n";
                                break;
                            }

                            // Hiển thị danh sách playlist
                            std::cout << "Available Playlists:\n";
                            for (size_t i = 0; i < playlists.size(); ++i)
                            {
                                std::cout << i + 1 << ": " << playlists[i]->getName() << "\n";
                            }

                            // Yêu cầu người dùng chọn playlist
                            std::cout << "Enter the number of the playlist to remove a song from: ";
                            int playlistIndex;
                            std::cin >> playlistIndex;

                            // Kiểm tra lựa chọn hợp lệ
                            if (playlistIndex < 1 || playlistIndex > playlists.size())
                            {
                                std::cerr << "Invalid playlist selection.\n";
                                break;
                            }
                            auto selectedPlaylist = playlists[playlistIndex - 1];

                            // Hiển thị danh sách bài hát trong playlist
                            auto songs = selectedPlaylist->getSongs();
                            if (songs.empty())
                            {
                                std::cout << "No songs in the selected playlist.\n";
                                break;
                            }

                            std::cout << "Songs in playlist '" << selectedPlaylist->getName() << "':\n";
                            for (size_t i = 0; i < songs.size(); ++i)
                            {
                                std::cout << i + 1 << ": " << songs[i].getName() << " (" << songs[i].getType() << ")\n";
                            }

                            // Yêu cầu người dùng chọn bài hát để xóa
                            std::cout << "Enter the number of the song to remove: ";
                            int songIndex;
                            std::cin >> songIndex;

                            // Kiểm tra lựa chọn hợp lệ
                            if (songIndex < 1 || songIndex > songs.size())
                            {
                                std::cerr << "Invalid song selection.\n";
                                break;
                            }

                            // Xóa bài hát khỏi playlist
                            auto songToRemove = songs[songIndex - 1];
                            selectedPlaylist->removeSong(songToRemove);
                            std::cout << "Song '" << songToRemove.getName() << "' removed from playlist '" << selectedPlaylist->getName() << "' successfully!\n";
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << "Error: " << e.what() << "\n";
                        }
                        catch (...)
                        {
                            std::cerr << "An unknown error occurred.\n";
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

void PlaylistController::writeDataToFileFormatted(const std::string& filename, const std::map<std::string, std::string>& data) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Unable to open file " << filename << " for writing.\n";
        return;
    }

    for (const auto& [playlistName, songs] : data) {
        outFile << "=== Playlist: " << playlistName << " ===\n";
        if (songs.empty()) {
            outFile << "(No songs in this playlist)\n\n";
        } else {
            size_t index = 1;
            std::istringstream songStream(songs);
            std::string song;
            while (std::getline(songStream, song, ',')) {
                outFile << index++ << ". " << song << "\n";
            }
            outFile << "\n";
        }
    }
    outFile.close();
}

