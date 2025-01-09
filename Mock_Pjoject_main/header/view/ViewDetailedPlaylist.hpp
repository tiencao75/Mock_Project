#ifndef VIEWDETAILEDPLAYLIST_H
#define VIEWDETAILEDPLAYLIST_H

#include "ViewBase.h"
#include <vector>
#include <string>

class ViewDetailedPlaylist : public ViewBase
{
public:
    void showPlaylistDetails(const std::string &playlistName, const std::vector<std::string> &songs);
    void addMediaFileToPlaylist(const std::string &fileName);
    void removeMediaFileFromPlaylist(const std::string &fileName);
    void show() override;
    void hide() override;
    void handleInput(const std::string &input) override;
};

#endif