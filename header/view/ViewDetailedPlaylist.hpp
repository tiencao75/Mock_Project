#ifndef VIEWDETAILEDPLAYLIST_HPP
#define VIEWDETAILEDPLAYLIST_HPP

#include "ViewBase.hpp"
#include <string>
#include "PlayList.hpp"
#include "MediaFile.hpp"

class ViewDetailedPlaylist : public ViewBase {
public:
    void show() override;
    void hide() override;
    void update(const std::string& data) override;
    std::string getName() const override;

    void showPlaylistDetails(const Playlist& playlist);
    void addMediaFileToPlaylist(const MediaFile& file);
    void removeMediaFileFromPlaylist(const MediaFile& file);
};

#endif // VIEWDETAILEDPLAYLIST_HPP
