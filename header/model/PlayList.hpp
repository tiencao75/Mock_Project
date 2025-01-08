#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <string>
#include <vector>
#include "MediaFile.hpp"

class Playlist {
private:
    std::string name;
    std::vector<MediaFile> songs;

public:
    Playlist(const std::string& name);

    // Getters
    std::string getName() const;
    std::vector<MediaFile> getSongs() const;

    bool operator==(const Playlist& other) const;
    // Methods
    void addSong(const MediaFile& song);
    void removeSong(const MediaFile& song);
};

#endif // PLAYLIST_HPP
