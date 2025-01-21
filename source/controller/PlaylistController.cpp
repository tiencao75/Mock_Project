#include "PlaylistController.hpp"
#include "ExceptionLib.hpp"
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



void PlaylistController::handleInput() {
    viewManager.getCurrentView()->hide();
    const std::string filename = "playlistsData.txt";
    bool isManagingPlaylist = true;

    while (isManagingPlaylist) {
        viewManager.getCurrentView()->hide();
        viewManager.getView("ViewPlaylist")->show();


        size_t choice;
        Exception_Handler("Enter your choice: ", choice, validatePlaylistsMenu);

        try {
            auto selection = static_cast<PlaylistOption>(choice);
            switch (selection) {

                case PlaylistOption::Create: { // Create Playlist
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
                        viewManager.getCurrentView()->pauseScreen();
                    } else {
                        // Thêm playlist mới nếu tên không trùng lặp
                        modelManager.getPlaylistLibrary().addPlaylist(
                            playlists.size() + 1, // Index mới cho playlist
                            Playlist(playlistName)
                        );
                        std::cout << "Playlist '" << playlistName << "' created successfully!\n";
                    }
                    viewManager.getCurrentView()->pauseScreen();

                    break;
                }


                case PlaylistOption::Delete: { // Delete Playlist
                    viewManager.getCurrentView()->hide();
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                    // Kiểm tra nếu không có playlist nào
                    if (playlists.empty()) {
                        std::cout << "No playlists available to delete.\n";
                        viewManager.getCurrentView()->pauseScreen();
                        break;
                    }

                    // Hiển thị danh sách playlist
                    std::cout << std::left << std::setw(10) << "Index" << std::setw(30) << "Playlist Name" << "\n";
                    std::cout << std::string(40, '-') << "\n";
                    for (const auto& [index, playlist] : playlists) {
                        std::cout << std::left << std::setw(10) << index << std::setw(30) << playlist->getName() << "\n";
                    }

                    size_t index;
                    Exception_Handler("Enter the index of the playlist to delete: ", index, validatePosInteger);

                    // Kiểm tra nếu index hợp lệ
                    if (playlists.find(index) == playlists.end()) {
                        std::cout << "[ERROR] Playlist with index " << index << " does not exist.\n";
                    } else {
                        // Xác nhận xóa playlist
                        std::cout << "Are you sure you want to delete the playlist '" << playlists[index]->getName()
                                << "'? (y/n): ";
                        char confirmation;
                        std::cin >> confirmation;
                        std::cin.ignore();

                        if (std::tolower(confirmation) != 'y') {
                            std::cout << "[INFO] Deletion canceled.\n";
                            viewManager.getCurrentView()->pauseScreen();
                            break;
                        }

                        // Xóa playlist
                        modelManager.getPlaylistLibrary().removePlaylist(index);
                        viewManager.getCurrentView()->hide();
                        std::cout << "[INFO] Playlist with index " << index << " has been deleted successfully!\n";

                        // Cập nhật lại danh sách
                        std::cout << "[INFO] Updating playlist indexes...\n";
                        auto updatedPlaylists = modelManager.getPlaylistLibrary().getAllPlaylists();
                        std::map<unsigned int, std::shared_ptr<Playlist>> reorderedPlaylists;
                        unsigned int newIndex = 1;

                        for (const auto& [oldIndex, playlist] : updatedPlaylists) {
                            reorderedPlaylists[newIndex++] = playlist;
                        }

                        modelManager.getPlaylistLibrary().setPlaylists(reorderedPlaylists);

                        // Hiển thị danh sách đã cập nhật
                        std::cout << "\n=== Updated Playlist Indexes ===\n";
                        std::cout << std::left << std::setw(10) << "Index" << std::setw(30) << "Playlist Name" << "\n";
                        std::cout << std::string(40, '-') << "\n";
                        for (const auto& [newIndex, playlist] : reorderedPlaylists) {
                            std::cout << std::left << std::setw(10) << newIndex << std::setw(30) << playlist->getName() << "\n";
                        }
                    }

                    // Tạm dừng trước khi quay lại menu
                    viewManager.getCurrentView()->pauseScreen();
                    break;
                }

                case PlaylistOption::ViewPlaylist: { // View All Playlists
                    viewManager.getCurrentView()->hide();
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
                    if (playlists.empty()) {
                        std::cout << "No playlists available.\n";
                        viewManager.getCurrentView()->pauseScreen();
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
                    viewManager.getCurrentView()->pauseScreen();
                    break;
                }

                case PlaylistOption::AddSong: { // Add Song to Playlist
                    viewManager.getCurrentView()->hide();
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                    // Kiểm tra nếu không có playlist nào
                    if (playlists.empty()) {
                        std::cout << "No playlists available. Please create a playlist first.\n";
                        viewManager.getCurrentView()->pauseScreen();
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

                    size_t playlistIndex;
                    Exception_Handler("Enter the index of the playlist to add a song to: ", playlistIndex, validatePosInteger);

                    // Kiểm tra nếu index hợp lệ
                    if (playlists.find(playlistIndex) == playlists.end()) {
                        std::cout << "Error: Playlist with index " << playlistIndex << " does not exist.\n";
                        viewManager.getCurrentView()->pauseScreen();
                        break;
                    }

                    auto playlist = playlists[playlistIndex];

                    const auto& mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
                    if (mediaFiles.empty()) {
                        std::cout << "No media files available to add.\n";
                        viewManager.getCurrentView()->pauseScreen();
                        break;
                    }

                    viewManager.getCurrentView()->hide();
                    modelManager.getMediaLibrary().displayPaginatedFiles(mediaFiles);

                    size_t fileID;
                    Exception_Handler("Enter the ID of the song to add: ", fileID, validatePosInteger);

                    try {
                        auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
                        if (!mediaFile) {
                            std::cout << "Error: No media file found with the given ID.\n";
                            viewManager.getCurrentView()->pauseScreen();
                            break;
                        }
                        // Tiếp tục xử lý mediaFile...
                        unsigned int newSongID = playlist->getSongs().size() + 1;

                        playlist->addSong(newSongID, *mediaFile);
                        // std::cout << "\nSong '" << mediaFile->getName() << "' added successfully to playlist '"
                        //         << playlist->getName() << "' with ID " << newSongID << ".\n";
                        viewManager.getCurrentView()->pauseScreen();

                        break;
                    } catch (const std::out_of_range& e) {
                        std::cout << "Error: No media file found with the given ID.\n";
                        viewManager.getCurrentView()->pauseScreen();
                        break;
                    }



                }

                case PlaylistOption::RemoveSong: { // Remove Song from Playlist
                    viewManager.getCurrentView()->hide();
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                    // Kiểm tra nếu không có playlist nào
                    if (playlists.empty()) {
                        std::cout << "No playlists available. Please create a playlist first.\n";
                        viewManager.getCurrentView()->pauseScreen();
                        break;
                    }

                    // Hiển thị danh sách playlist
                    while (true) {
                        viewManager.getCurrentView()->hide();
                        std::cout << "\nAvailable Playlists:\n";
                        std::cout << std::left << std::setw(10) << "Index"
                                << std::setw(30) << "Playlist Name" << "\n";
                        std::cout << std::string(40, '-') << "\n";
                        for (const auto& [index, playlist] : playlists) {
                            std::cout << std::left << std::setw(10) << index
                                    << std::setw(30) << playlist->getName() << "\n";
                        }

                        // Nhập playlist index với xử lý lỗi
                        size_t playlistIndex;
                        Exception_Handler("Enter the index of the playlist to remove a song from: ", playlistIndex, validatePosInteger);

                        if (playlists.find(playlistIndex) == playlists.end()) {
                            std::cout << "Error: Playlist with index " << playlistIndex << " does not exist.\n";
                            viewManager.getCurrentView()->pauseScreen();
                            continue; // Hiển thị lại danh sách và cho nhập lại
                        }

                    auto playlist = playlists[playlistIndex];

                        // Lấy danh sách bài hát trong playlist
                        const auto& songs = playlist->getSongs();
                        if (songs.empty()) {
                            std::cout << "No songs in the selected playlist.\n";
                            viewManager.getCurrentView()->pauseScreen();
                            break;
                        }

                    viewManager.getCurrentView()->hide();

                    std::cout << "\nSongs in playlist '" << playlist->getName() << "':\n";
                    std::cout << std::left << std::setw(10) << "ID"
                            << std::setw(30) << "Song Name" << "\n";
                    std::cout << std::string(40, '-') << "\n";
                    for (const auto& [id, song] : songs) {
                        std::cout << std::left << std::setw(10) << id
                                << std::setw(30) << song.getName() << "\n";
                    }

                        // Nhập song ID với xử lý lỗi
                        size_t songID;
                        Exception_Handler("Enter the ID of the song to remove: ", songID, validatePosInteger);

                        if (songs.find(songID) == songs.end()) {
                            std::cout << "Error: Song with ID " << songID << " does not exist in the playlist.\n";
                            viewManager.getCurrentView()->pauseScreen();
                            continue; // Hiển thị lại danh sách và cho nhập lại
                        }

                        // Xác nhận xóa bài hát
                        char confirm;
                        std::cout << "Are you sure you want to remove the song '" << songs.at(songID).getName()
                                << "' from playlist '" << playlist->getName() << "'? (y/n): ";
                        std::cin >> confirm;

                        if (confirm != 'y' && confirm != 'Y') {
                            std::cout << "Operation cancelled.\n";
                            viewManager.getCurrentView()->pauseScreen();
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

                        viewManager.getCurrentView()->pauseScreen();
                        break; // Thoát khỏi case sau khi hoàn tất
                    }

                    break; // Thoát khỏi case chính
                }


                case PlaylistOption::ViewSong: { // View Songs in a Playlist
                    auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();

                    // Kiểm tra nếu không có playlist nào
                    if (playlists.empty()) {
                        std::cout << "No playlists available. Please create a playlist first.\n";
                        viewManager.getCurrentView()->pauseScreen();
                        break;
                    }

                    while (true) {
                        viewManager.getCurrentView()->hide(); // Ẩn menu hiện tại
                        std::cout << "\nAvailable Playlists:\n";
                        std::cout << std::left << std::setw(10) << "Index"
                                << std::setw(30) << "Playlist Name" << "\n";
                        std::cout << std::string(40, '-') << "\n";
                        for (const auto& [index, playlist] : playlists) {
                            std::cout << std::left << std::setw(10) << index
                                    << std::setw(30) << playlist->getName() << "\n";
                        }

                        // Nhập playlist index với xử lý lỗi
                        size_t playlistIndex;
                        Exception_Handler("Enter the index of the playlist to view songs: ", playlistIndex, validatePosInteger);

                        // Kiểm tra nếu index không tồn tại
                        if (playlists.find(playlistIndex) == playlists.end()) {
                            std::cout << "Error: Playlist with index " << playlistIndex << " does not exist.\n";
                            viewManager.getCurrentView()->pauseScreen();
                            continue; // Cho phép nhập lại
                        }

                    auto playlist = playlists[playlistIndex];

                        // Lấy danh sách bài hát trong playlist
                        const auto& songs = playlist->getSongs();
                        if (songs.empty()) {
                            std::cout << "\nNo songs in playlist '" << playlist->getName() << "'.\n";
                            viewManager.getCurrentView()->pauseScreen();
                            break;
                        }

                        // Hiển thị danh sách bài hát
                        viewManager.getCurrentView()->hide();
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

                        viewManager.getCurrentView()->pauseScreen();
                        break; // Thoát khi xem xong
                    }

                    break;
                }



                case PlaylistOption::Exit: // Exit Playlist Menu
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







