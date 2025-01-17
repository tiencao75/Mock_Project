// #ifndef PLAYLIST_LIBRARY_HPP
// #define PLAYLIST_LIBRARY_HPP

// #include <vector>
// #include "PlayList.hpp"

// class PlaylistLibrary {
// private:
//     std::vector<Playlist> playlists;

// public:
//     PlaylistLibrary();
//     std::vector<Playlist> getAllPlaylists() const;
//     void addPlaylist(const Playlist& playlist);
//     void removePlaylist(const Playlist& playlist);
//     Playlist& getPlaylistByName(const std::string& name)const;
// };

// #endif // PLAYLIST_LIBRARY_HPP
// #ifndef PLAYLIST_LIBRARY_HPP
// #define PLAYLIST_LIBRARY_HPP

// #include <vector>
// #include <memory>
// #include "PlayList.hpp"

// class PlaylistLibrary {
// private:
//     std::vector<std::shared_ptr<Playlist>> playlists; // Danh sách các playlist sử dụng con trỏ thông minh

// public:
//     PlaylistLibrary();

//     // Trả về danh sách tất cả playlist (tham chiếu hằng để tránh sao chép)
//     const std::vector<std::shared_ptr<Playlist>>& getAllPlaylists() const;

//     // Thêm playlist vào danh sách
//     void addPlaylist(const Playlist& playlist);

//     // Xóa playlist khỏi danh sách
//     void removePlaylist(const std::string& name);

//     // Lấy playlist theo tên
//     std::shared_ptr<Playlist> getPlaylistByName(const std::string& name) const;
// };

// #endif // PLAYLIST_LIBRARY_HPP


#ifndef PLAYLIST_LIBRARY_HPP
#define PLAYLIST_LIBRARY_HPP

#include <map>
#include <memory>
#include "PlayList.hpp"

class PlaylistLibrary {
private:
    std::map<unsigned int, std::shared_ptr<Playlist>> playlists; // Sử dụng map để quản lý playlist theo index

public:
    PlaylistLibrary();

    // Trả về danh sách tất cả playlist (tham chiếu hằng để tránh sao chép)
    const std::map<unsigned int, std::shared_ptr<Playlist>>& getAllPlaylists() const;

    // Thêm playlist vào danh sách với index
    void addPlaylist(unsigned int index, const Playlist& playlist);

    // Xóa playlist khỏi danh sách theo index
    void removePlaylist(unsigned int index);

    // Lấy playlist theo index
    std::shared_ptr<Playlist> getPlaylistByIndex(unsigned int index) const;

    void setPlaylists(const std::map<unsigned int, std::shared_ptr<Playlist>>& newPlaylists);
    std::map<unsigned int, MediaFile>& getSongs();

};

#endif // PLAYLIST_LIBRARY_HPP
