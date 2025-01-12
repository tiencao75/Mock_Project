#ifndef PLAYLIST_LIBRARY_HPP
#define PLAYLIST_LIBRARY_HPP

#include <vector>
#include <memory>
#include "PlayList.hpp"

class PlaylistLibrary {
private:
    std::vector<std::shared_ptr<Playlist>> playlists; // Danh sách các playlist sử dụng con trỏ thông minh

public:
    PlaylistLibrary();

    // Trả về danh sách tất cả playlist (tham chiếu hằng để tránh sao chép)
    const std::vector<std::shared_ptr<Playlist>>& getAllPlaylists() const;

    // Thêm playlist vào danh sách
    void addPlaylist(const Playlist& playlist);

    // Xóa playlist khỏi danh sách
    void removePlaylist(const std::string& name);

    // Lấy playlist theo tên
    std::shared_ptr<Playlist> getPlaylistByName(const std::string& name) const;
};

#endif // PLAYLIST_LIBRARY_HPP
