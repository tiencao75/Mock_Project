#include "PlaylistController.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include<iomanip>

// Constructor
PlaylistController::PlaylistController(ModelManager& modelManager, ViewManager& viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

// Destructor
PlaylistController::~PlaylistController() {}

// Handle user input for playlist management
void PlaylistController::handleInput() {
    const std::string filename = "playlistsData.txt";
    try {
        readPlaylistsFromFile(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
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

        try {
            switch (choice) {

                case 1: { // Create Playlist
                    std::cout << "\nEnter the name of the new playlist: ";
                    std::string playlistName;
                    std::getline(std::cin, playlistName);

                    // Kiểm tra nếu tên playlist đã tồn tại
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
                    bool isDuplicate = false;

                    for (const auto& [index, playlist] : playlists) {
                        if (playlist->getName() == playlistName) {
                            isDuplicate = true;
                            break;
                        }
                    }

                    if (isDuplicate) {
                        std::cout << "Error: A playlist with the name '" << playlistName << "' already exists.\n";
                    } else {
                        // Thêm playlist mới nếu tên không trùng lặp
                        modelManager.getPlaylistLibrary().addPlaylist(
                            playlists.size() + 1, // Index mới cho playlist
                            Playlist(playlistName)
                        );
                        std::cout << "Playlist '" << playlistName << "' created successfully!\n";
                    }

                    break;
                }


                case 2: { // Delete Playlist
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                    // Kiểm tra nếu không có playlist nào
                    if (playlists.empty()) {
                        std::cout << "No playlists available to delete.\n";
                        break;
                    }

                    // // Hiển thị danh sách playlist
                    // std::cout << "Available Playlists:\n";
                    // for (const auto& [index, playlist] : playlists) {
                    //     std::cout << "Index: " << index << ", Name: " << playlist->getName() << "\n";
                    // }
                    std::cout << std::left << std::setw(10) << "Index"<< std::setw(30) << "Playlist Name" << "\n";
                    std::cout << std::string(40, '-') << "\n"; // Dòng gạch ngang phân cách

                    for (const auto& [index, playlist] : playlists) {std::cout << std::left << std::setw(10) << index<< std::setw(30) << playlist->getName() << "\n";
}

                    // Yêu cầu người dùng nhập index để xóa
                    std::cout << "Enter the index of the playlist to delete: ";
                    unsigned int index;
                    std::cin >> index;

                    // Kiểm tra nếu index hợp lệ
                    if (playlists.find(index) == playlists.end()) {
                        std::cout << "Error: Playlist with index " << index << " does not exist.\n";
                    } else {
                        // Xóa playlist
                        modelManager.getPlaylistLibrary().removePlaylist(index);
                        std::cout << "Playlist with index " << index << " deleted successfully!\n";

                        // Cập nhật lại index của các playlist còn lại
                        auto updatedPlaylists = modelManager.getPlaylistLibrary().getAllPlaylists();
                        std::map<unsigned int, std::shared_ptr<Playlist>> reorderedPlaylists;
                        unsigned int newIndex = 1;

                        for (const auto& [oldIndex, playlist] : updatedPlaylists) {
                            reorderedPlaylists[newIndex++] = playlist;
                        }

                        // Ghi lại thứ tự mới vào PlaylistLibrary
                        modelManager.getPlaylistLibrary().setPlaylists(reorderedPlaylists);

                        // Hiển thị danh sách sau khi cập nhật
                        std::cout << "Updated Playlist Indexes:\n";
                        for (const auto& [newIndex, playlist] : reorderedPlaylists) {
                            std::cout << "Index: " << newIndex << ", Name: " << playlist->getName() << "\n";
                        }
                    }

                    break;
                }

                case 3: { // View All Playlists
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
                    if (playlists.empty()) {
                        std::cout << "No playlists available.\n";
                        break;
                    }

                    // Hiển thị tiêu đề dạng bảng
                    std::cout << std::left << std::setw(10) << "Index"
                            << std::setw(30) << "Playlist Name" << "\n";
                    std::cout << std::string(40, '-') << "\n"; // Dòng gạch ngang phân cách

                    // Hiển thị các playlist
                    for (const auto& [index, playlist] : playlists) {
                        std::cout << std::left << std::setw(10) << index
                                << std::setw(30) << playlist->getName() << "\n";
                    }
                    break;
                }




                // case 3: { // View All Playlists
                //     auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
                //     if (playlists.empty()) {
                //         std::cout << "No playlists available.\n";
                //         break;
                //     }

                //     std::cout << "Available Playlists:\n";
                //     for (const auto& [index, playlist] : playlists) {
                //         std::cout << "Index: " << index << ", Name: " << playlist->getName() << "\n";
                //     }
                //     break;
                // }

                // case 4: { // Add Song to Playlist
                //     auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                //     // Kiểm tra nếu không có playlist nào
                //     if (playlists.empty()) {
                //         std::cout << "No playlists available. Please create a playlist first.\n";
                //         break;
                //     }

                //     // Hiển thị danh sách playlist
                //     std::cout << "Available Playlists:\n";
                //     for (const auto& [index, playlist] : playlists) {
                //         std::cout << "Index: " << index << ", Name: " << playlist->getName() << "\n";
                //     }

                //     // Yêu cầu người dùng nhập index để chọn playlist
                //     std::cout << "Enter the index of the playlist to add a song to: ";
                //     unsigned int playlistIndex;
                //     std::cin >> playlistIndex;

                //     // Kiểm tra nếu index hợp lệ
                //     if (playlists.find(playlistIndex) == playlists.end()) {
                //         std::cout << "Error: Playlist with index " << playlistIndex << " does not exist.\n";
                //         break;
                //     }

                //     auto playlist = playlists[playlistIndex];

                //     // Lấy danh sách các tệp media
                //     const auto& mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
                //     if (mediaFiles.empty()) {
                //         std::cout << "No media files available to add.\n";
                //         break;
                //     }

                //     // Hiển thị danh sách các tệp media
                //     std::cout << "Available Media Files (ID: Name):\n";
                //     for (const auto& [id, file] : mediaFiles) {
                //         std::cout << id << ": " << file->getName() << "\n";
                //     }

                //     // Yêu cầu người dùng nhập ID bài hát cần thêm
                //     std::cout << "Enter the ID of the song to add: ";
                //     unsigned int fileID;
                //     std::cin >> fileID;

                //     // Kiểm tra và lấy bài hát từ MediaLibrary
                //     auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
                //     if (!mediaFile) {
                //         std::cout << "Error: No media file found with the given ID.\n";
                //         break;
                //     }

                //     // Tính toán ID mới cho bài hát trong playlist
                //     unsigned int newSongID = playlist->getSongs().size() + 1;

                //     // Thêm bài hát vào playlist với ID tự động tăng
                //     playlist->addSong(newSongID, *mediaFile);
                //     std::cout << "Song '" << mediaFile->getName() << "' added successfully to playlist '"
                //             << playlist->getName() << "' with ID " << newSongID << ".\n";

                //     break;
                // }


                case 4: { // Add Song to Playlist
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                    // Kiểm tra nếu không có playlist nào
                    if (playlists.empty()) {
                        std::cout << "No playlists available. Please create a playlist first.\n";
                        break;
                    }

                    // Hiển thị danh sách playlist
                    std::cout << "\nAvailable Playlists:\n";
                    std::cout << std::left << std::setw(10) << "Index"
                            << std::setw(30) << "Playlist Name" << "\n";
                    std::cout << std::string(40, '-') << "\n";
                    for (const auto& [index, playlist] : playlists) {
                        std::cout << std::left << std::setw(10) << index
                                << std::setw(30) << playlist->getName() << "\n";
                    }

                    // Yêu cầu người dùng nhập index để chọn playlist
                    std::cout << "\nEnter the index of the playlist to add a song to: ";
                    unsigned int playlistIndex;
                    std::cin >> playlistIndex;

                    // Kiểm tra nếu index hợp lệ
                    if (playlists.find(playlistIndex) == playlists.end()) {
                        std::cout << "Error: Playlist with index " << playlistIndex << " does not exist.\n";
                        break;
                    }

                    auto playlist = playlists[playlistIndex];

                    // Lấy danh sách các tệp media
                    const auto& mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
                    if (mediaFiles.empty()) {
                        std::cout << "No media files available to add.\n";
                        break;
                    }

                    // Hiển thị danh sách các tệp media
                    std::cout << "\nAvailable Media Files:\n";
                    std::cout << std::left << std::setw(10) << "ID"
                            << std::setw(30) << "Name" << "\n";
                    std::cout << std::string(40, '-') << "\n";
                    for (const auto& [id, file] : mediaFiles) {
                        std::cout << std::left << std::setw(10) << id
                                << std::setw(30) << file->getName() << "\n";
                    }

                    // Yêu cầu người dùng nhập ID bài hát cần thêm
                    std::cout << "\nEnter the ID of the song to add: ";
                    unsigned int fileID;
                    std::cin >> fileID;

                    // Kiểm tra và lấy bài hát từ MediaLibrary
                    auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
                    if (!mediaFile) {
                        std::cout << "Error: No media file found with the given ID.\n";
                        break;
                    }

                    // Tính toán ID mới cho bài hát trong playlist
                    unsigned int newSongID = playlist->getSongs().size() + 1;

                    // Thêm bài hát vào playlist với ID tự động tăng
                    playlist->addSong(newSongID, *mediaFile);
                    std::cout << "\nSong '" << mediaFile->getName() << "' added successfully to playlist '"
                            << playlist->getName() << "' with ID " << newSongID << ".\n";

                    break;
                }



                // case 5: { // Remove Song from Playlist
                //     auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                //     // Kiểm tra nếu không có playlist nào
                //     if (playlists.empty()) {
                //         std::cout << "No playlists available. Please create a playlist first.\n";
                //         break;
                //     }

                //     // Hiển thị danh sách playlist
                //     std::cout << "Available Playlists:\n";
                //     for (const auto& [index, playlist] : playlists) {
                //         std::cout << "Index: " << index << ", Name: " << playlist->getName() << "\n";
                //     }

                //     // Yêu cầu người dùng nhập index để chọn playlist
                //     std::cout << "Enter the index of the playlist to remove a song from: ";
                //     unsigned int playlistIndex;
                //     std::cin >> playlistIndex;

                //     // Kiểm tra nếu index hợp lệ
                //     if (playlists.find(playlistIndex) == playlists.end()) {
                //         std::cout << "Error: Playlist with index " << playlistIndex << " does not exist.\n";
                //         break;
                //     }

                //     auto playlist = playlists[playlistIndex];

                //     // Hiển thị danh sách bài hát trong playlist
                //     const auto& songs = playlist->getSongs();
                //     if (songs.empty()) {
                //         std::cout << "No songs in the selected playlist.\n";
                //         break;
                //     }

                //     std::cout << "Songs in playlist '" << playlist->getName() << "':\n";
                //     for (const auto& [id, song] : songs) {
                //         std::cout << id << ": " << song.getName() << "\n";
                //     }

                //     // Yêu cầu người dùng nhập ID bài hát cần xóa
                //     std::cout << "Enter the ID of the song to remove: ";
                //     unsigned int songID;
                //     std::cin >> songID;

                //     // Kiểm tra nếu ID hợp lệ
                //     if (songs.find(songID) == songs.end()) {
                //         std::cout << "Error: Song with ID " << songID << " does not exist in the playlist.\n";
                //         break;
                //     }

                //     // Xóa bài hát
                //     playlist->removeSong(songID);
                //     std::cout << "Song with ID " << songID << " removed successfully from playlist '" << playlist->getName() << "'.\n";

                //     // Tự động dồn lại ID để lấp chỗ trống
                //     auto updatedSongs = playlist->getSongs();
                //     std::map<unsigned int, MediaFile> reorderedSongs;
                //     unsigned int newID = 1;

                //     for (const auto& [oldID, song] : updatedSongs) {
                //         reorderedSongs.emplace(newID++, song); // Sử dụng emplace để tránh lỗi constructor mặc định
                //     }

                //     // Ghi lại danh sách bài hát đã sắp xếp lại
                //     playlist->setSongs(reorderedSongs);

                //     // Hiển thị danh sách bài hát sau khi cập nhật
                //     std::cout << "Updated Songs in playlist '" << playlist->getName() << "':\n";
                //     for (const auto& [id, song] : reorderedSongs) {
                //         std::cout << id << ": " << song.getName() << "\n";
                //     }

                //     break;
                // }

                case 5: { // Remove Song from Playlist
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                    // Kiểm tra nếu không có playlist nào
                    if (playlists.empty()) {
                        std::cout << "No playlists available. Please create a playlist first.\n";
                        break;
                    }

                    // Hiển thị danh sách playlist
                    std::cout << "\nAvailable Playlists:\n";
                    std::cout << std::left << std::setw(10) << "Index"
                            << std::setw(30) << "Playlist Name" << "\n";
                    std::cout << std::string(40, '-') << "\n";
                    for (const auto& [index, playlist] : playlists) {
                        std::cout << std::left << std::setw(10) << index
                                << std::setw(30) << playlist->getName() << "\n";
                    }

                    // Yêu cầu người dùng nhập index để chọn playlist
                    std::cout << "\nEnter the index of the playlist to remove a song from: ";
                    unsigned int playlistIndex;
                    std::cin >> playlistIndex;

                    // Kiểm tra nếu index hợp lệ
                    if (playlists.find(playlistIndex) == playlists.end()) {
                        std::cout << "Error: Playlist with index " << playlistIndex << " does not exist.\n";
                        break;
                    }

                    auto playlist = playlists[playlistIndex];

                    // Hiển thị danh sách bài hát trong playlist
                    const auto& songs = playlist->getSongs();
                    if (songs.empty()) {
                        std::cout << "No songs in the selected playlist.\n";
                        break;
                    }

                    std::cout << "\nSongs in playlist '" << playlist->getName() << "':\n";
                    std::cout << std::left << std::setw(10) << "ID"
                            << std::setw(30) << "Song Name" << "\n";
                    std::cout << std::string(40, '-') << "\n";
                    for (const auto& [id, song] : songs) {
                        std::cout << std::left << std::setw(10) << id
                                << std::setw(30) << song.getName() << "\n";
                    }

                    // Yêu cầu người dùng nhập ID bài hát cần xóa
                    std::cout << "\nEnter the ID of the song to remove: ";
                    unsigned int songID;
                    std::cin >> songID;

                    // Kiểm tra nếu ID hợp lệ
                    if (songs.find(songID) == songs.end()) {
                        std::cout << "Error: Song with ID " << songID << " does not exist in the playlist.\n";
                        break;
                    }

                    // Xóa bài hát
                    playlist->removeSong(songID);
                    std::cout << "\nSong with ID " << songID << " removed successfully from playlist '"
                            << playlist->getName() << "'.\n";

                    // Tự động dồn lại ID để lấp chỗ trống
                    auto updatedSongs = playlist->getSongs();
                    std::map<unsigned int, MediaFile> reorderedSongs;
                    unsigned int newID = 1;

                    for (const auto& [oldID, song] : updatedSongs) {
                        reorderedSongs.emplace(newID++, song); // Sử dụng emplace để tránh lỗi constructor mặc định
                    }

                    // Ghi lại danh sách bài hát đã sắp xếp lại
                    playlist->setSongs(reorderedSongs);

                    // Hiển thị danh sách bài hát sau khi cập nhật
                    std::cout << "\nUpdated Songs in playlist '" << playlist->getName() << "':\n";
                    std::cout << std::left << std::setw(10) << "ID"
                            << std::setw(30) << "Song Name" << "\n";
                    std::cout << std::string(40, '-') << "\n";
                    for (const auto& [id, song] : reorderedSongs) {
                        std::cout << std::left << std::setw(10) << id
                                << std::setw(30) << song.getName() << "\n";
                    }

                    break;
                }


                // case 6: { // View Songs in a Playlist
                //     auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                //     // Kiểm tra nếu không có playlist nào
                //     if (playlists.empty()) {
                //         std::cout << "No playlists available. Please create a playlist first.\n";
                //         break;
                //     }

                //     // Hiển thị danh sách playlist
                //     std::cout << "Available Playlists:\n";
                //     for (const auto& [index, playlist] : playlists) {
                //         std::cout << "Index: " << index << ", Name: " << playlist->getName() << "\n";
                //     }

                //     // Yêu cầu người dùng nhập index để chọn playlist
                //     std::cout << "Enter the index of the playlist to view songs: ";
                //     unsigned int playlistIndex;
                //     std::cin >> playlistIndex;

                //     // Kiểm tra nếu index hợp lệ
                //     if (playlists.find(playlistIndex) == playlists.end()) {
                //         std::cout << "Error: Playlist with index " << playlistIndex << " does not exist.\n";
                //         break;
                //     }

                //     auto playlist = playlists[playlistIndex];

                //     // Lấy danh sách bài hát trong playlist
                //     const auto& songs = playlist->getSongs();
                //     if (songs.empty()) {
                //         std::cout << "No songs in playlist '" << playlist->getName() << "'.\n";
                //     } else {
                //         std::cout << "Songs in playlist '" << playlist->getName() << "':\n";
                //         for (const auto& [id, song] : songs) {
                //             std::cout << id << ": " << song.getName() << "\n";
                //         }
                //     }

                //     break;
                // }

                case 6: { // View Songs in a Playlist
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                    // Kiểm tra nếu không có playlist nào
                    if (playlists.empty()) {
                        std::cout << "No playlists available. Please create a playlist first.\n";
                        break;
                    }

                    // Hiển thị danh sách playlist
                    std::cout << "\nAvailable Playlists:\n";
                    std::cout << std::left << std::setw(10) << "Index"
                            << std::setw(30) << "Playlist Name" << "\n";
                    std::cout << std::string(40, '-') << "\n";
                    for (const auto& [index, playlist] : playlists) {
                        std::cout << std::left << std::setw(10) << index
                                << std::setw(30) << playlist->getName() << "\n";
                    }

                    // Yêu cầu người dùng nhập index để chọn playlist
                    std::cout << "\nEnter the index of the playlist to view songs: ";
                    unsigned int playlistIndex;
                    std::cin >> playlistIndex;

                    // Kiểm tra nếu index hợp lệ
                    if (playlists.find(playlistIndex) == playlists.end()) {
                        std::cout << "Error: Playlist with index " << playlistIndex << " does not exist.\n";
                        break;
                    }

                    auto playlist = playlists[playlistIndex];

                    // Lấy danh sách bài hát trong playlist
                    const auto& songs = playlist->getSongs();
                    if (songs.empty()) {
                        std::cout << "\nNo songs in playlist '" << playlist->getName() << "'.\n";
                    } else {
                        std::cout << "\nSongs in playlist '" << playlist->getName() << "':\n";
                        std::cout << std::left << std::setw(10) << "ID"
                                << std::setw(30) << "Song Name" 
                                << std::setw(20) << "Type" << "\n";
                        std::cout << std::string(60, '-') << "\n";
                        for (const auto& [id, song] : songs) {
                            std::cout << std::left << std::setw(10) << id
                                    << std::setw(30) << song.getName()
                                    << std::setw(20) << song.getType() << "\n";
                        }
                    }

                    break;
                }



                case 0: // Exit Playlist Menu
                    isManagingPlaylist = false;
                    writePlaylistsToFile(filename);
                    break;

                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    }
}


void PlaylistController::writePlaylistsToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Unable to open file " << filename << " for writing.\n";
        return;
    }

    const auto& playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
    for (const auto& [index, playlist] : playlists) {
        outFile << "Playlist: " << playlist->getName() << "\n";

        const auto& songs = playlist->getSongs();
        for (const auto& [songID, song] : songs) {
            outFile << songID << "," << song.getPath() << "," << song.getType() << "\n";
        }

        outFile << "---\n"; // Dấu phân cách giữa các playlist
    }

    outFile.close();
    std::cout << "Playlists saved to file: " << filename << "\n";
}



void PlaylistController::readPlaylistsFromFile(const std::string& filename) {
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




