#include "ViewPlay.hpp"
#include <iostream>

void ViewPlay::show() {
    std::cout << "Displaying Play View..." << std::endl;
}

void ViewPlay::hide() {
    std::cout << "Hiding Play View..." << std::endl;
}

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
