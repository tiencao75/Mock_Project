// #include "PlaylistController.hpp"
// #include "ModelManager.hpp"
// #include "PlaylistLibrary.hpp"
// #include <iostream>

// // Constructor
// PlaylistController::PlaylistController(ControllerManager* manager)
//     : controllerManager(manager) {
//     // No initialization needed for now
// }

// // Destructor
// PlaylistController::~PlaylistController() {
//     // Cleanup if necessary
// }

// // Method to get all playlists
// std::vector<Playlist> PlaylistController::getAllPlaylists() {
//     // Use controllerManager to access the ModelManager and get all playlists from PlaylistLibrary
//     return controllerManager->getModelManager().getPlaylistLibrary().getAllPlaylists();
// }

// // Method to create a new playlist
// void PlaylistController::createPlaylist(const std::string& name) {
//     // Create a new Playlist object with the provided name
//     Playlist newPlaylist;
//     newPlaylist.setName(name);

//     // Use controllerManager to access the ModelManager and add the new playlist
//     controllerManager->getModelManager().getPlaylistLibrary().addPlaylist(newPlaylist);
//     std::cout << "Playlist '" << name << "' created successfully." << std::endl;
// }

// // Method to delete a playlist by its name
// void PlaylistController::deletePlaylist(const std::string& name) {
//     // Get the playlist by name using the controllerManager
//     Playlist* playlist = controllerManager->getModelManager().getPlaylistLibrary().getPlaylistByName(name);

//     if (playlist != nullptr) {
//         // If the playlist exists, remove it
//         controllerManager->getModelManager().getPlaylistLibrary().removePlaylist(*playlist);
//         std::cout << "Playlist '" << name << "' deleted successfully." << std::endl;
//     } else {
//         std::cout << "Playlist '" << name << "' not found." << std::endl;
//     }
// }