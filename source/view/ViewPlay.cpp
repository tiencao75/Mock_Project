#include "ViewPlay.hpp"
#include <iostream>

void ViewPlay::show() {
    std::cout << "\n╔════════════════════════════════════════════╗\n";
    std::cout << "║         🎬 Media Playback Menu 🎵          ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    std::cout << "║  [1] ➤ Play Current Media                  ║\n";
    std::cout << "║  [2] ➤ Pause Current Media                 ║\n";
    std::cout << "║  [3] ➤ Resume Current Media                ║\n";
    std::cout << "║  [4] ➤ Stop Current Media                  ║\n";
    std::cout << "║  [5] ➤ Play Specific Media File            ║\n";
    std::cout << "║  [6] ➤ Play Playlist                       ║\n";
    std::cout << "║  [7] ➤ Skip to Next Media                  ║\n";
    std::cout << "║  [8] ➤ Skip to Previous Media              ║\n";
    std::cout << "║  [9] ➤ Adjust Volume                       ║\n";
    std::cout << "║  [0] ➤ Exit Playback Menu                  ║\n";
    std::cout << "╚════════════════════════════════════════════╝\n";
    std::cout << "👉 Enter your choice: ";

}

// void ViewPlay::hide() {
//     std::cout << "Hiding Play View..." << std::endl;
// }

void ViewPlay::update(const std::string& data) {
    std::cout << "Updating Play View with data: " << data << std::endl;
}

std::string ViewPlay::getName() const {
    return "ViewPlay";
}

void ViewPlay::showPlayerControls() {
    std::cout << "Player Controls: [Play] [Pause] [Stop] [Next] [Previous]" << std::endl;
}

void ViewPlay::showSongInfo(const MediaFile& file) {
    std::cout << "Now Playing: " << file.getName() << std::endl;
}
