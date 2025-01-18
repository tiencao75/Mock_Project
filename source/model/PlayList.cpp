// #include "PlayList.hpp"
// #include <algorithm> // For std::find
// #include <stdexcept> // For exceptions

// // Constructor
// Playlist::Playlist(const std::string& name) : name(name) {}

// // Getter for name
// std::string Playlist::getName() const {
//     return name;
// }

// // Getter for songs
// std::vector<MediaFile> Playlist::getSongs() const {
//     return songs;
// }
// // Toán tử so sánh ==
// bool Playlist::operator==(const Playlist& other) const {
//     return name == other.name && songs == other.songs;
// }
// // Add a song to the playlist
// void Playlist::addSong(const MediaFile& song) {
//     if (std::find(songs.begin(), songs.end(), song) != songs.end()) {
//         throw std::runtime_error("Song already exists in the playlist");
//     }
//     songs.push_back(song);
// }

// // Remove a song from the playlist
// void Playlist::removeSong(const MediaFile& song) {
//     auto it = std::find(songs.begin(), songs.end(), song);
//     if (it == songs.end()) {
//         throw std::runtime_error("Song not found in the playlist");
//     }
//     songs.erase(it);
// }

#include "PlayList.hpp"
#include <stdexcept> // For exceptions

// Constructor
Playlist::Playlist(const std::string& name) : name(name) {}

// Getter for name
std::string Playlist::getName() const {
    return name;
}

// Getter for songs
const std::map<unsigned int, MediaFile>& Playlist::getSongs() const {
    return songs;
}

// Comparison operator
bool Playlist::operator==(const Playlist& other) const {
    return name == other.name && songs == other.songs;
}

// Add a song to the playlist
void Playlist::addSong(unsigned int id, const MediaFile& song) {
    try {
        // Sử dụng emplace để thêm bài hát vào map
        auto result = songs.emplace(id, song);

        // Kiểm tra kết quả của emplace
        if (!result.second) {
            // Nếu emplace không thành công (ID đã tồn tại)
            std::cerr << "Error: A song with ID " << id << " already exists in the playlist." << std::endl;
        } else {
            // Nếu thêm thành công
            std::cout << "Song '" << song.getName() << "' added to the playlist with ID: " << id << std::endl;
        }
    } catch (const std::exception& e) {
        // Xử lý ngoại lệ nếu có lỗi trong quá trình thêm
        std::cerr << "Exception while adding song: " << e.what() << std::endl;
    }
}


// Remove a song from the playlist
void Playlist::removeSong(unsigned int id) {
    // Tìm bài hát theo ID
    auto it = songs.find(id);
    
    // Kiểm tra nếu ID không tồn tại
    if (it == songs.end()) {
        throw std::runtime_error("Song with the given ID does not exist in the playlist.");
    }

    // Xóa bài hát khỏi danh sách
    songs.erase(it);

    // Thông báo thành công
    std::cout << "Song with ID " << id << " has been removed successfully from the playlist." << std::endl;
}


// Get a song by ID
std::shared_ptr<MediaFile> Playlist::getSongById(unsigned int id) const {
    // Tìm bài hát theo ID trong map
    auto it = songs.find(id);

    // Nếu không tìm thấy, ném ngoại lệ
    if (it == songs.end()) {
        throw std::runtime_error("Error: Song with ID " + std::to_string(id) + " not found in the playlist.");
    }

    // Tạo và trả về con trỏ thông minh trỏ đến bài hát
    auto songPtr = std::make_shared<MediaFile>(it->second);

    // Hiển thị thông tin bài hát
    std::cout << "Song metadata for ID " << id << ": " << std::endl;
    std::cout << "Name: " << songPtr->getName() << std::endl;

    // Lấy và hiển thị metadata (nếu được hỗ trợ)
    Metadata metadata = songPtr->getMetadata();
    std::map<std::string, std::string> data = metadata.getData();
    for (const auto& [key, value] : data) {
        std::cout << key << ": " << (value.empty() ? "unknown" : value) << std::endl;
    }

    return songPtr; // Trả về con trỏ thông minh trỏ đến bài hát
}

void Playlist::setSongs(const std::map<unsigned int, MediaFile>& newSongs) {
    songs = newSongs;
}


