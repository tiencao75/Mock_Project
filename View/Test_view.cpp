#include "ViewScanfOption.h"
#include "ViewMediaFile.h"
#include "ViewPlaylist.h"
#include "ViewDetailedPlaylist.h"
#include "ViewPlay.h"
#include "ViewMetadata.h"
#include "ViewManager.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>

int main()
{
    // Initialize views
    ViewScanfOption scanView;
    ViewMediaFile mediaView;
    ViewPlaylist playlistView;
    ViewDetailedPlaylist detailedPlaylistView;
    ViewPlay playView;
    ViewMetadata metadataView;
    ViewManager manager;

    // Example usage of ViewManager
    manager.addView(std::make_unique<ViewScanfOption>());
    manager.addView(std::make_unique<ViewMediaFile>());
    manager.addView(std::make_unique<ViewPlaylist>());
    manager.addView(std::make_unique<ViewDetailedPlaylist>());
    manager.addView(std::make_unique<ViewPlay>());
    manager.addView(std::make_unique<ViewMetadata>());

    // // Switch to scan view and use its functionality
    manager.switchView(&scanView);
    // scanView.showScanMenu();
    // std::string dir = scanView.getDirectoryInput();
    // std::cout << "Scanned directory: " << dir << std::endl;

    // // Switch to media view and display files
    // manager.switchView(&mediaView);
    // std::vector<std::string> files = {"File1.mp3", "File2.mp3", "File3.mp3"};
    // mediaView.showMediaFilesPage(files, 0);
    // mediaView.nextPage();
    // mediaView.previousPage();

    // // Switch to playlist view and display playlists
    // manager.switchView(&playlistView);
    // std::vector<std::string> playlists = {"Workout", "Chill", "Party"};
    // playlistView.showPlaylistMenu();
    // playlistView.showPlaylistList(playlists);
    // playlistView.selectPlaylist("Workout");

    // // Switch to detailed playlist view
    // manager.switchView(&detailedPlaylistView);
    // std::vector<std::string> songs = {"Song1.mp3", "Song2.mp3"};
    // detailedPlaylistView.showPlaylistDetails("Workout", songs);
    // detailedPlaylistView.addMediaFileToPlaylist("NewSong.mp3");
    // detailedPlaylistView.removeMediaFileFromPlaylist("Song2.mp3");

    // // Switch to play view and show controls
    // manager.switchView(&playView);
    // playView.showPlayerControls();
    // playView.showSongInfo("Song1.mp3");

    // // Switch to metadata view and manipulate metadata
    // manager.switchView(&metadataView);
    // std::map<std::string, std::string> metadata = {
    //     {"Title", "Song1"},
    //     {"Artist", "Artist1"},
    //     {"Album", "Album1"},
    //     {"Year", "2022"}};
    // metadataView.showFileMetadata(metadata);
    // metadataView.editFileMetadata(metadata, "Artist", "NewArtist");
    // metadataView.showFileMetadata(metadata);

    return 0;
}
