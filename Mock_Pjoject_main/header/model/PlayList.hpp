#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <string>
#include <vector>
#include <memory>
#include "MediaFile.hpp"

class Playlist
{
private:
    std::string name;
    std::vector<std::shared_ptr<MediaFile>> Songs;

public:
    Playlist(const std::string &name);

    // Getters
    std::string getName() const;
    std::vector<std::shared_ptr<MediaFile>> getSongs() const;

    // Methods
    void addSong(const std::shared_ptr<MediaFile> &song);
    void removeSong(const std::shared_ptr<MediaFile> &song);
};

#endif // PLAYLIST_HPP
