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

// #include "PlaylistLibrary.hpp"
// #include <algorithm>
// #include <stdexcept>

// // Constructor
// PlaylistLibrary::PlaylistLibrary() {}

// // Trả về danh sách tất cả playlist (tham chiếu hằng)
// const std::vector<std::shared_ptr<Playlist>>& PlaylistLibrary::getAllPlaylists() const {
//     return playlists;
// }

// // Thêm playlist vào danh sách
// void PlaylistLibrary::addPlaylist(const Playlist& playlist) {
//     // Kiểm tra nếu playlist đã tồn tại theo tên
//     for (const auto& p : playlists) {
//         if (p->getName() == playlist.getName()) {
//             throw std::runtime_error("Playlist already exists");
//         }
//     }
//     playlists.push_back(std::make_shared<Playlist>(playlist)); // Tạo con trỏ thông minh và thêm vào danh sách
// }

// // Xóa playlist khỏi danh sách theo tên
// void PlaylistLibrary::removePlaylist(const std::string& name) {
//     auto it = std::remove_if(playlists.begin(), playlists.end(),
//                              [&name](const std::shared_ptr<Playlist>& p) {
//                                  return p->getName() == name; // So sánh theo tên
//                              });
//     if (it == playlists.end()) {
//         throw std::runtime_error("Playlist not found");
//     }
//     playlists.erase(it, playlists.end()); // Xóa playlist
// }

// // Lấy playlist theo tên
// std::shared_ptr<Playlist> PlaylistLibrary::getPlaylistByName(const std::string& name) const {
//     for (const auto& playlist : playlists) {
//         if (playlist->getName() == name) {
//             return playlist; // Trả về con trỏ thông minh
//         }
//     }
//     throw std::runtime_error("Playlist not found");
// }


#include "PlaylistLibrary.hpp"
#include <stdexcept>

// Constructor
PlaylistLibrary::PlaylistLibrary() {}

// Trả về danh sách tất cả playlist (tham chiếu hằng)
const std::map<unsigned int, std::shared_ptr<Playlist>>& PlaylistLibrary::getAllPlaylists() const {
    return playlists;
}

// Thêm playlist vào danh sách với index
void PlaylistLibrary::addPlaylist(unsigned int index, const Playlist& playlist) {
    try {
        // Sử dụng emplace để thêm playlist vào map
        auto result = playlists.emplace(index, std::make_shared<Playlist>(playlist));

        // Kiểm tra kết quả của emplace
        if (!result.second) {
            // Nếu index đã tồn tại
            std::cerr << "Error: A playlist with index " << index << " already exists." << std::endl;
        } else {
            // Thông báo thêm thành công
            std::cout << "Playlist added successfully at index: " << index << std::endl;
        }
    } catch (const std::exception& e) {
        // Xử lý ngoại lệ trong quá trình thêm
        std::cerr << "Exception while adding playlist: " << e.what() << std::endl;
    }
}


// Xóa playlist khỏi danh sách theo index
void PlaylistLibrary::removePlaylist(unsigned int index) {
    try {
        // Tìm playlist theo index
        auto it = playlists.find(index);

        // Kiểm tra nếu index không tồn tại
        if (it == playlists.end()) {
            throw std::runtime_error("Error: Playlist with index " + std::to_string(index) + " not found.");
        }

        // Xóa playlist khỏi map
        playlists.erase(it);

        // Thông báo thành công
        std::cout << "Playlist with index " << index << " has been removed successfully." << std::endl;
    } catch (const std::exception& e) {
        // Xử lý ngoại lệ và thông báo lỗi
        std::cerr << "Exception while removing playlist: " << e.what() << std::endl;
    }
}


// Lấy playlist theo index
std::shared_ptr<Playlist> PlaylistLibrary::getPlaylistByIndex(unsigned int index) const {
    try {
        // Tìm playlist theo index
        auto it = playlists.find(index);

        // Nếu không tìm thấy, ném ngoại lệ
        if (it == playlists.end()) {
            throw std::runtime_error("Error: Playlist with index " + std::to_string(index) + " not found.");
        }

        // Trả về con trỏ thông minh trỏ đến playlist
        return it->second;
    } catch (const std::exception& e) {
        // Xử lý ngoại lệ và ghi log lỗi nếu cần
        std::cerr << "Exception in getPlaylistByIndex: " << e.what() << std::endl;
        throw; // Ném lại ngoại lệ để gọi hàm xử lý tiếp
    }
}

void PlaylistLibrary::setPlaylists(const std::map<unsigned int, std::shared_ptr<Playlist>>& newPlaylists) {
    playlists = newPlaylists;
}


