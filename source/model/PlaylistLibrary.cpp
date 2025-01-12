// #include "PlaylistLibrary.hpp"
// #include <algorithm>
// #include <stdexcept>

// std::vector<Playlist> PlaylistLibrary::getAllPlaylists() const {
//     return playlists;
// }

// PlaylistLibrary::PlaylistLibrary() {}

// void PlaylistLibrary::addPlaylist(const Playlist& playlist) {
//     playlists.push_back(playlist);
// }

// void PlaylistLibrary::removePlaylist(const Playlist& playlist) {
//     playlists.erase(std::remove(playlists.begin(), playlists.end(), playlist), playlists.end());
// }

// Playlist PlaylistLibrary::getPlaylistByName(const std::string& name) const {
//     for (const auto& playlist : playlists) {
//         if (playlist.getName() == name) {
//             return playlist;
//         }
//     }
//     throw std::runtime_error("Playlist not found");
// }

#include "PlaylistLibrary.hpp"
#include <algorithm>
#include <stdexcept>

// Constructor
PlaylistLibrary::PlaylistLibrary() {}

// Trả về danh sách tất cả playlist (tham chiếu hằng)
const std::vector<std::shared_ptr<Playlist>>& PlaylistLibrary::getAllPlaylists() const {
    return playlists;
}

// Thêm playlist vào danh sách
void PlaylistLibrary::addPlaylist(const Playlist& playlist) {
    // Kiểm tra nếu playlist đã tồn tại theo tên
    for (const auto& p : playlists) {
        if (p->getName() == playlist.getName()) {
            throw std::runtime_error("Playlist already exists");
        }
    }
    playlists.push_back(std::make_shared<Playlist>(playlist)); // Tạo con trỏ thông minh và thêm vào danh sách
}

// Xóa playlist khỏi danh sách theo tên
void PlaylistLibrary::removePlaylist(const std::string& name) {
    auto it = std::remove_if(playlists.begin(), playlists.end(),
                             [&name](const std::shared_ptr<Playlist>& p) {
                                 return p->getName() == name; // So sánh theo tên
                             });
    if (it == playlists.end()) {
        throw std::runtime_error("Playlist not found");
    }
    playlists.erase(it, playlists.end()); // Xóa playlist
}

// Lấy playlist theo tên
std::shared_ptr<Playlist> PlaylistLibrary::getPlaylistByName(const std::string& name) const {
    for (const auto& playlist : playlists) {
        if (playlist->getName() == name) {
            return playlist; // Trả về con trỏ thông minh
        }
    }
    throw std::runtime_error("Playlist not found");
}