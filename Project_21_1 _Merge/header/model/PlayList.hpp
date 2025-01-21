// #ifndef PLAYLIST_HPP
// #define PLAYLIST_HPP

// #include <string>
// #include <vector>
// #include "MediaFile.hpp"

// class Playlist {
// private:
//     std::string name;
//     std::vector<MediaFile> songs;

// public:
//     Playlist(const std::string& name);

//     // Getters
//     std::string getName() const;
//     std::vector<MediaFile> getSongs() const;

//     bool operator==(const Playlist& other) const;
//     // Methods
//     void addSong(const MediaFile& song);
//     void removeSong(const MediaFile& song);
// };

// #endif // PLAYLIST_HPP

#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <string>
#include <iostream>
#include <memory>

#include <map>
#include "MediaFile.hpp"

class Playlist {
private:
    std::string name;
    std::map<unsigned int, MediaFile> songs; // Use map to manage songs by ID

public:
    Playlist(const std::string& name);

    // Getters
    std::string getName() const;
    const std::map<unsigned int, MediaFile>& getSongs() const;

    bool operator==(const Playlist& other) const;

    // Methods
    void addSong(unsigned int id, const MediaFile& song);
    void removeSong(unsigned int id);
    std::shared_ptr<MediaFile> getSongById(unsigned int id) const ;

    void setSongs(const std::map<unsigned int, MediaFile>& newSongs);
};

#endif // PLAYLIST_HPP
