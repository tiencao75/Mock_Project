#ifndef VIEWPLAYLIST_H
#define VIEWPLAYLIST_H

#include "ViewBase.hpp"
#include <vector>
#include <string>

class ViewPlaylist : public ViewBase
{
public:
    void show() override;
    void hide() override;
    void handleInput(const std::string &input) override;
    void showPlaylistMenu();
    void showPlaylistList(const std::vector<std::string> &playlists);
    void selectPlaylist(const std::string &playlist);
};

#endif