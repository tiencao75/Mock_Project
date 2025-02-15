// #include <iostream>
// #include <filesystem>
// #include "MediaFile.hpp"
// #include "Metadata.hpp"

// namespace fs = std::filesystem;

// void showAllFiles(const std::string& directory) {
//     std::cout << "\nFiles in directory " << directory << ":\n" << std::endl;
//     int index = 1;
//     for (const auto& entry : fs::directory_iterator(directory)) {
//         if (fs::is_regular_file(entry)) {
//             std::cout << index++ << ". " << entry.path().filename().string() << std::endl;
//         }
//     }
// }

// void printMetadata(const Metadata& metadata) {
//     std::cout << "\n=== Metadata Information ===" << std::endl;
//     for (const auto& [key, value] : metadata.getData()) {
//         std::cout << key << ": " << value << std::endl;
//     }
// }
// void restoreMetadata(MediaFile& mediaFile, const Metadata& originalMetadata) {
//     mediaFile.setMetadata(originalMetadata);
//     originalMetadata.saveToFile(mediaFile.getPath());
//     std::cout << "Original metadata restored successfully." << std::endl;
// }

// void editMetadata(MediaFile& mediaFile) {
//     Metadata metadata = mediaFile.getMetadata();
//     Metadata originalMetadata = metadata; // Save original metadata for restoration
//     printMetadata(metadata);

//     int choice;
//     do {
//         std::cout << "\nChoose an option to edit metadata:" << std::endl;
//         std::cout << "1. Edit Title" << std::endl;
//         std::cout << "2. Edit Artist" << std::endl;
//         std::cout << "3. Edit Album" << std::endl;
//         std::cout << "4. Edit Genre" << std::endl;
//         std::cout << "5. Edit Year" << std::endl;
//         std::cout << "6. Edit Track" << std::endl;
//         std::cout << "7. Restore Original Values" << std::endl;
//         std::cout << "0. Exit Editing" << std::endl;
//         std::cout << "Enter your choice: ";
//         std::cin >> choice;
//         std::cin.ignore();

//         std::string newValue;
//         switch (choice) {
//             case 1:
//                 std::cout << "Enter new title: ";
//                 std::getline(std::cin, newValue);
//                 metadata.setValue("Title", newValue);
//                 break;
//             case 2:
//                 std::cout << "Enter new artist: ";
//                 std::getline(std::cin, newValue);
//                 metadata.setValue("Artist", newValue);
//                 break;
//             case 3:
//                 std::cout << "Enter new album: ";
//                 std::getline(std::cin, newValue);
//                 metadata.setValue("Album", newValue);
//                 break;
//             case 4:
//                 std::cout << "Enter new genre: ";
//                 std::getline(std::cin, newValue);
//                 metadata.setValue("Genre", newValue);
//                 break;
//             case 5:
//                 std::cout << "Enter new year: ";
//                 std::getline(std::cin, newValue);
//                 metadata.setValue("Year", newValue);
//                 break;
//             case 6:
//                 std::cout << "Enter new track: ";
//                 std::getline(std::cin, newValue);
//                 metadata.setValue("Track", newValue);
//                 break;
//             case 7:
//                 std::cout << "Restoring original values..." << std::endl;
//                 restoreMetadata(mediaFile, originalMetadata);
//                 break;
//             case 0:
//                 std::cout << "Exiting editing..." << std::endl;
//                 break;
//             default:
//                 std::cout << "Invalid choice, please try again." << std::endl;
//         }

//         if (choice != 0 && choice != 7) {
//             mediaFile.setMetadata(metadata);
//             std::cout << "Metadata updated successfully." << std::endl;
//             printMetadata(metadata);
//         }
//     } while (choice != 0);
// }

// int main() {
//     const std::string mediaDir = "/home/tienck/Documents/Music"; // Change this to your music directory
//     int choice;

//     do {
//         std::cout << "\nChoose an option:" << std::endl;
//         std::cout << "1. Show All Files in Music Folder" << std::endl;
//         std::cout << "0. Exit" << std::endl;
//         std::cout << "Enter your choice: ";
//         std::cin >> choice;
//         std::cin.ignore();

//         if (choice == 1) {
//             showAllFiles(mediaDir);

//             std::cout << "\nEnter the number of the file you want to edit: ";
//             int fileChoice;
//             std::cin >> fileChoice;
//             std::cin.ignore();

//             int currentIndex = 1;
//             std::string filepath;
//             for (const auto& entry : fs::directory_iterator(mediaDir)) {
//                 if (fs::is_regular_file(entry)) {
//                     if (currentIndex == fileChoice) {
//                         filepath = entry.path().string();
//                         break;
//                     }
//                     currentIndex++;
//                 }
//             }

//             if (!filepath.empty()) {
//                 try {
//                     MediaFile mediaFile(filepath, filepath, "audio");
//                     editMetadata(mediaFile);
//                 } catch (const std::exception& e) {
//                     std::cerr << "Error: " << e.what() << std::endl;
//                 }
//             } else {
//                 std::cerr << "Invalid file choice." << std::endl;
//             }
//         }
//     } while (choice != 0);

//     return 0;
// }

#include "ControllerManager.hpp"
#include "ViewScanfOption.hpp"
#include "ViewMainMenu.hpp"
#include <iostream>

int main() {
    // Khởi tạo ControllerManager
    ControllerManager controllerManager;

    // Chạy chương trình
    std::cout << "=== Starting Application ===" << std::endl;
    controllerManager.handleInputData();

    std::cout << "=== Application Ended ===" << std::endl;

    return 0;
}
