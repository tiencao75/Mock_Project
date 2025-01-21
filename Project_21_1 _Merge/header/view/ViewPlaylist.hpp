#ifndef VIEWPLAYLIST_HPP
#define VIEWPLAYLIST_HPP

#include "ViewBase.hpp"
#include <string>
#include <vector>
#include "PlayList.hpp"

class ViewPlaylist : public ViewBase {
public:
    void show() override;
    // void hide() override;
    void update(const std::string& data) override;
    std::string getName() const override;

    void showPlaylistMenu();
    void showPlaylistList(const std::vector<Playlist>& playlists);
    void selectPlaylist(const Playlist& playlist);
};

#endif // VIEWPLAYLIST_HPP
