#include "ViewMainMenu.hpp"
#include <iostream>

void ViewMainMenu::show() {
    std::cout << "Displaying Main Menu..." << std::endl;
}

// void ViewMainMenu::hide() {
//     std::cout << "Hiding Main Menu..." << std::endl;
// }

void ViewMainMenu::update(const std::string& data) {
    std::cout << "Updating Main Menu View with data: " << data << std::endl;
}

std::string ViewMainMenu::getName() const {
    return "ViewMainMenu";
}

void ViewMainMenu::showMainMenu() {
    //std::cout << "=== Main Menu ===\n1. Scan Options\n2. MediaFiledData\n3. Edit metadata\n4. ManagerPlayList\n5. Play mediafile\n0. Exit\n";
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║                                        ║\n";
    std::cout << "║              🌟 MAIN MENU 🌟           ║\n";
    std::cout << "║                                        ║\n";
    std::cout << "╠════════════════════════════════════════╣\n";
    std::cout << "║  1. 🔍 Scan Options                    ║\n";
    std::cout << "║  2. 📂 Media Filed Data                ║\n";
    std::cout << "║  3. ✏️  Edit Metadata                   ║\n";
    std::cout << "║  4. 🎵 Manage Playlists                ║\n";
    std::cout << "║  5. 🎬 Play Media File                 ║\n";
    std::cout << "║  0. ❌ Exit                            ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
}

void ViewMainMenu::handleMenuSelection(int selection) {
    switch (selection) {
        case 1:
            std::cout << "Navigating to Scan Options..." << std::endl;
            break;
        case 2:
            std::cout << "Navigating to Play Media..." << std::endl;
            break;
        case 3:
            std::cout << "Navigating to Playlist Manager..." << std::endl;
            break;
        case 0:
            std::cout << "Exiting application..." << std::endl;
            break;
        default:
            std::cerr << "Invalid option. Please try again." << std::endl;
    }
}
