#include "ViewPlaylist.h"
#include <iostream>
void ViewPlaylist::show()
{
    std::cout << "Showing playlist view..." << std::endl;
}

void ViewPlaylist::hide()
{
    std::cout << "Hiding playlist view..." << std::endl;
}

void ViewPlaylist::handleInput(const std::string &input)
{
    std::cout << "Handling input for playlist view: " << input << std::endl;
}
void ViewPlaylist::showPlaylistMenu()
{
    std::cout << "Playlist Menu:" << std::endl;
    std::cout << "1. View all playlists" << std::endl;
    std::cout << "2. Select a playlist" << std::endl;
    std::cout << "3. Create a new playlist" << std::endl;
    std::cout << "4. Delete a playlist" << std::endl;
}

void ViewPlaylist::showPlaylistList(const std::vector<std::string> &playlists)
{
    std::cout << "Available Playlists:" << std::endl;
    for (const auto &playlist : playlists)
    {
        std::cout << "- " << playlist << std::endl;
    }
}

void ViewPlaylist::selectPlaylist(const std::string &playlist)
{
    std::cout << "Selected Playlist: " << playlist << std::endl;
}