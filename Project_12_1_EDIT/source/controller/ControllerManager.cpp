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
      playingMediaController(modelManager, viewManager)
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
// Getter cho ModelManager
ModelManager &ControllerManager::getModelManager()
{
    return modelManager;
}

// Getter cho ViewManager
ViewManager &ControllerManager::getViewManager()
{
    return viewManager;
}

// Hàm đọc dữ liệu từ file
std::map<std::string, std::string> ControllerManager::readDataFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::map<std::string, std::string> data;

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty() || line[0] == '#')
                continue; // Bỏ qua dòng trống hoặc comment
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos)
            {
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
void ControllerManager::writeDataToFile(const std::string &filename, const std::map<std::string, std::string> &data)
{
    std::ofstream file(filename);

    if (file.is_open())
    {
        for (const auto &[key, value] : data)
        {
            file << key << "=" << value << "\n";
        }
        file.close();
    }
}

void ControllerManager::handleInputData()
{
    // Bước 1: Gọi hàm handleInput trong ScanfOptionController
    scanfOptionController.handleInput();

    // Bước 2: Hiển thị menu chính
    bool isRunning = true;
    while (isRunning)
    {
        // Hiển thị Main Menu
        mainMenuController.showMainMenu();

        // Đọc lựa chọn của người dùng
        int selectionInput;
        std::cin >> selectionInput;
        auto selection = static_cast<MainMenuOption>(selectionInput);

        switch (selection)
        {
        case MainMenuOption::ShowAllMediaFiles:
        { // Hiển thị tất cả file media
            // Lấy danh sách file từ MediaLibrary thông qua ModelManager
            const auto &mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
            auto *mediaFileView = dynamic_cast<ViewMediaFile *>(viewManager.getView("ViewMediaFile"));

            if (mediaFileView)
            {
                if (mediaFiles.empty())
                {
                    mediaFileView->update("No media files found.");
                }
                else
                {
                    mediaFileView->update("Displaying all media files with IDs:");
                    for (const auto &[id, file] : mediaFiles)
                    { // Duyệt qua std::map
                        if (file)
                        { // Kiểm tra null pointer
                            mediaFileView->update(std::to_string(id) + ": " + file->getName() + " (" + file->getType() + ")");
                        }
                    }
                }
            }
            break;
        }

        case MainMenuOption::ShowMetadata:
        { // Hiển thị metadata của một file
            auto *metadataView = dynamic_cast<ViewMetadata *>(viewManager.getView("ViewMetadata"));

            if (metadataView)
            {
                try
                {
                    // Hiển thị danh sách file với ID
                    const auto &mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
                    if (mediaFiles.empty())
                    {
                        metadataView->update("No media files available to show metadata.");
                    }
                    else
                    {
                        metadataView->update("Available Media Files (ID: Name):");
                        for (const auto &[id, file] : mediaFiles)
                        {
                            metadataView->update(std::to_string(id) + ": " + file->getName());
                        }

                        // Yêu cầu người dùng nhập ID để xem metadata
                        metadataView->update("Enter the ID of the file to view metadata: ");
                        unsigned int fileID;
                        std::cin >> fileID;

                        // Lấy file từ ID và hiển thị metadata
                        auto mediaFile = modelManager.getMediaLibrary().getMediaFileByIndex(fileID);
                        if (!mediaFile)
                        {
                            metadataView->update("Error: File with the provided ID does not exist.");
                        }
                        else
                        {
                            const auto &metadata = mediaFile->getMetadata().getData();
                            if (metadata.empty())
                            {
                                metadataView->update("No metadata available for the selected file.");
                            }
                            else
                            {
                                metadataView->update("Metadata for file '" + mediaFile->getName() + "':");
                                for (const auto &[key, value] : metadata)
                                {
                                    metadataView->update(key + ": " + value);
                                }
                            }
                        }
                    }
                }
                catch (const std::exception &e)
                {
                    metadataView->update("An error occurred while fetching metadata: " + std::string(e.what()));
                }
                catch (...)
                {
                    metadataView->update("An unknown error occurred while fetching metadata.");
                }
            }
            else
            {
                std::cerr << "Error: Metadata view not available.\n";
            }
            break;
        }

        case MainMenuOption::EditMetadata:
        { // Sửa metadata
            metadataController.handleInput();
            break;
        }
        case MainMenuOption::ManagerPlayList:
        {
            auto *playlistView = dynamic_cast<ViewPlaylist *>(viewManager.getView("ViewPlaylist"));
            if (playlistView)
            {
                bool isManagingPlaylist = true;
                while (isManagingPlaylist)
                {
                    // Hiển thị menu Playlist
                    std::cout << "\nPlaylist Menu: [1] Create [2] Delete [3] View [4] Add Song [5] Remove Song [0] Exit\n";
                    std::cout << "Enter your choice: ";
                    int playlistMenuOption;
                    std::cin >> playlistMenuOption;

                    switch (playlistMenuOption)
                    {
                    case 1:
                    { // Create Playlist
                        std::cout << "Enter the name of the new playlist: ";
                        std::string playlistName;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                        std::getline(std::cin, playlistName);

                        Playlist newPlaylist(playlistName);
                        try
                        {
                            modelManager.getPlaylistLibrary().addPlaylist(newPlaylist);
                            std::cout << "Playlist '" << playlistName << "' created successfully!\n";
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << "Error: " << e.what() << "\n";
                        }
                        break;
                    }
                    case 2:
                    { // Delete Playlist
                        std::cout << "Enter the name of the playlist to delete: ";
                        std::string playlistName;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                        std::getline(std::cin, playlistName);

                        try
                        {
                            modelManager.getPlaylistLibrary().removePlaylist(playlistName);
                            std::cout << "Playlist '" << playlistName << "' deleted successfully!\n";
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << "Error: " << e.what() << "\n";
                        }
                        break;
                    }
                    case 3:
                    { // View Playlists
                        auto playlists = modelManager.getPlaylistLibrary().getAllPlaylists();
                        if (playlists.empty())
                        {
                            std::cout << "No playlists available.\n";
                        }
                        else
                        {
                            std::cout << "Playlists:\n";
                            for (const auto &playlist : playlists)
                            {
                                std::cout << " - " << playlist->getName() << "\n";
                            }

                            std::cout << "\nEnter the name of the playlist to view details: ";
                            std::string playlistName;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                            std::getline(std::cin, playlistName);

                            try
                            {
                                auto selectedPlaylist = modelManager.getPlaylistLibrary().getPlaylistByName(playlistName);

                                std::cout << "Songs in playlist '" << playlistName << "':\n";
                                auto songs = selectedPlaylist->getSongs();
                                if (songs.empty())
                                {
                                    std::cout << "No songs in this playlist.\n";
                                }
                                else
                                {
                                    for (const auto &song : songs)
                                    {
                                        std::cout << " - " << song.getName() << " (" << song.getType() << ")\n";
                                    }
                                }
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << "Error: " << e.what() << "\n";
                            }
                        }
                        break;
                    }
                    case 4:
                    { // Add Song to Playlist
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
                    case 5:
                    { // Remove Song from Playlist
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
                    case 0:
                    { // Exit Playlist Menu
                        isManagingPlaylist = false;
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid option. Please try again.\n";
                    }
                    }
                }
            }
            else
            {
                std::cerr << "Error: Playlist View not found.\n";
            }
            break;
        }
        case MainMenuOption::PlayingMedia:
        {
            playingMediaController.handleInput();
            break;
        }

        case MainMenuOption::Exit:
        { // Thoát chương trình
            auto *mainMenuView = dynamic_cast<ViewMainMenu *>(viewManager.getView("ViewMainMenu"));
            if (mainMenuView)
            {
                mainMenuView->update("Exiting application...");
            }
            isRunning = false;
            break;
        }

        default:
        { // Lựa chọn không hợp lệ
            auto *mainMenuView = dynamic_cast<ViewMainMenu *>(viewManager.getView("ViewMainMenu"));
            if (mainMenuView)
            {
                mainMenuView->update("Invalid option. Please try again.");
            }
            break;
        }
        }
    }
}
