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
