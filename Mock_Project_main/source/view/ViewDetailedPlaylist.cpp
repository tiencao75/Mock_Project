#include "ViewDetailedPlaylist.hpp"
#include <iostream>

void ViewDetailedPlaylist::showPlaylistDetails(const std::string &playlistName, const std::vector<std::string> &songs)
{
    std::cout << "Details of Playlist: " << playlistName << std::endl;
    for (const auto &song : songs)
    {
        std::cout << "- " << song << std::endl;
    }
}

void ViewDetailedPlaylist::addMediaFileToPlaylist(const std::string &fileName)
{
    std::cout << "Added " << fileName << " to playlist." << std::endl;
}

void ViewDetailedPlaylist::removeMediaFileFromPlaylist(const std::string &fileName)
{
    std::cout << "Removed " << fileName << " from playlist." << std::endl;
}
void ViewDetailedPlaylist::show()
{
    std::cout << "Showing detailed playlist view..." << std::endl;
}

void ViewDetailedPlaylist::hide()
{
    std::cout << "Hiding detailed playlist view..." << std::endl;
}

void ViewDetailedPlaylist::handleInput(const std::string &input)
{
    std::cout << "Handling input for detailed playlist view: " << input << std::endl;
}