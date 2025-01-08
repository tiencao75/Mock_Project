// #include <iostream>
// #include "taglib.hpp"
// #include <iomanip>
// #include <filesystem>

// namespace fs = std::filesystem; // Sử dụng alias cho filesystem
// int main() {
// const std::string mediaDir = "/home/tienck/Documents/Music"; //music
//     int choice;
//     do
//     {
//         std::cout << "\nChoose an option:" << std::endl;
//         std::cout << "1. Show All Files in Music Folder" << std::endl;
//         std::cout << "0. Exit" << std::endl;
//         std::cout << "Enter your choice: ";
//         std::cin >> choice;
//         std::cin.ignore(); // Đọc bỏ newline

//         if (choice == 1)
//         {
//             showAllFiles(mediaDir);

//             std::cout << "\nEnter the number of the file you want to edit: ";
//             int fileChoice;
//             std::cin >> fileChoice;
//             std::cin.ignore(); // Đọc bỏ newline

//             int currentIndex = 1;
//             std::string filepath;
//             for (const auto &entry : fs::directory_iterator(mediaDir))
//             {
//                 if (fs::is_regular_file(entry))
//                 {
//                     if (currentIndex == fileChoice)
//                     {
//                         filepath = entry.path().string();
//                         break;
//                     }
//                     currentIndex++;
//                 }
//             }

//             if (!filepath.empty())
//             {
//                 TagLib::FileRef f(filepath.c_str());

//                 if (!f.isNull() && f.tag() && f.audioProperties())
//                 {
//                     TagLib::Tag *tag = f.tag();
//                     TagLib::AudioProperties *audioProperties = f.audioProperties();

//                     OriginalMetadata originalMetadata = {
//                         tag->title().toCString(),
//                         tag->artist().toCString(),
//                         tag->album().toCString(),
//                         tag->year(),
//                         tag->track(),
//                         tag->genre().toCString()};

//                     printMetadata(tag, audioProperties);

//                     int subChoice;
//                     do
//                     {
//                         std::cout << "\nChoose an option to edit metadata:" << std::endl;
//                         std::cout << "1. Edit Title" << std::endl;
//                         std::cout << "2. Edit Artist" << std::endl;
//                         std::cout << "3. Edit Album" << std::endl;
//                         std::cout << "4. Edit Genre" << std::endl;
//                         std::cout << "5. Edit Year" << std::endl;
//                         std::cout << "6. Edit Track" << std::endl;
//                         std::cout << "7. Restore Original Values" << std::endl;
//                         std::cout << "0. Exit Editing" << std::endl;
//                         std::cout << "Enter your choice: ";
//                         std::cin >> subChoice;
//                         std::cin.ignore(); // Đọc bỏ newline

//                         std::string newValue;
//                         unsigned int newYear;
//                         switch (subChoice)
//                         {
//                         case 1:
//                             std::cout << "Enter new title: ";
//                             std::getline(std::cin, newValue);
//                             tag->setTitle(TagLib::String(newValue));
//                             break;
//                         case 2:
//                             std::cout << "Enter new artist: ";
//                             std::getline(std::cin, newValue);
//                             tag->setArtist(TagLib::String(newValue));
//                             break;
//                         case 3:
//                             std::cout << "Enter new album: ";
//                             std::getline(std::cin, newValue);
//                             tag->setAlbum(TagLib::String(newValue));
//                             break;
//                         case 4:
//                             std::cout << "Enter new genre: ";
//                             std::getline(std::cin, newValue);
//                             tag->setGenre(TagLib::String(newValue));
//                             break;
//                         case 5:
//                             std::cout << "Enter new year: ";
//                             std::cin >> newYear;
//                             tag->setYear(newYear);
//                             std::cin.ignore(); // Đọc bỏ newline
//                             break;
//                         case 6:
//                             std::cout << "Enter new track number: ";
//                             std::cin >> newYear;
//                             tag->setTrack(newYear);
//                             std::cin.ignore(); // Đọc bỏ newline
//                             break;
//                         case 7:
//                             std::cout << "Restoring original values..." << std::endl;
//                             restoreMetadata(tag, originalMetadata);
//                             break;
//                         case 0:
//                             std::cout << "Exiting editing..." << std::endl;
//                             break;
//                         default:
//                             std::cout << "Invalid choice, please try again." << std::endl;
//                         }

//                         if (subChoice != 0)
//                         {
//                             printMetadata(tag, audioProperties);
//                         }
//                     } while (subChoice != 0);

//                     if (f.save())
//                     {
//                         std::cout << "\nMetadata updated successfully!" << std::endl;
//                     }
//                     else
//                     {
//                         std::cerr << "Error: Could not save changes to the file." << std::endl;
//                     }
//                 }
//                 else
//                 {
//                     std::cerr << "Error: Could not open file or retrieve metadata." << std::endl;
//                 }
//             }
//             else
//             {
//                 std::cerr << "Invalid file choice." << std::endl;
//             }
//         }

//     } while (choice != 0);
//     return 0;
// }

#include <iostream>
#include <filesystem>
#include "MediaFile.hpp"
#include "Metadata.hpp"

namespace fs = std::filesystem;

void showAllFiles(const std::string& directory) {
    std::cout << "\nFiles in directory " << directory << ":\n" << std::endl;
    int index = 1;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (fs::is_regular_file(entry)) {
            std::cout << index++ << ". " << entry.path().filename().string() << std::endl;
        }
    }
}

void printMetadata(const Metadata& metadata) {
    std::cout << "\n=== Metadata Information ===" << std::endl;
    for (const auto& [key, value] : metadata.getData()) {
        std::cout << key << ": " << value << std::endl;
    }
}
void restoreMetadata(MediaFile& mediaFile, const Metadata& originalMetadata) {
    mediaFile.setMetadata(originalMetadata);
    originalMetadata.saveToFile(mediaFile.getPath());
    std::cout << "Original metadata restored successfully." << std::endl;
}

void editMetadata(MediaFile& mediaFile) {
    Metadata metadata = mediaFile.getMetadata();
    Metadata originalMetadata = metadata; // Save original metadata for restoration
    printMetadata(metadata);

    int choice;
    do {
        std::cout << "\nChoose an option to edit metadata:" << std::endl;
        std::cout << "1. Edit Title" << std::endl;
        std::cout << "2. Edit Artist" << std::endl;
        std::cout << "3. Edit Album" << std::endl;
        std::cout << "4. Edit Genre" << std::endl;
        std::cout << "5. Edit Year" << std::endl;
        std::cout << "6. Edit Track" << std::endl;
        std::cout << "7. Restore Original Values" << std::endl;
        std::cout << "0. Exit Editing" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        std::string newValue;
        switch (choice) {
            case 1:
                std::cout << "Enter new title: ";
                std::getline(std::cin, newValue);
                metadata.setValue("Title", newValue);
                break;
            case 2:
                std::cout << "Enter new artist: ";
                std::getline(std::cin, newValue);
                metadata.setValue("Artist", newValue);
                break;
            case 3:
                std::cout << "Enter new album: ";
                std::getline(std::cin, newValue);
                metadata.setValue("Album", newValue);
                break;
            case 4:
                std::cout << "Enter new genre: ";
                std::getline(std::cin, newValue);
                metadata.setValue("Genre", newValue);
                break;
            case 5:
                std::cout << "Enter new year: ";
                std::getline(std::cin, newValue);
                metadata.setValue("Year", newValue);
                break;
            case 6:
                std::cout << "Enter new track: ";
                std::getline(std::cin, newValue);
                metadata.setValue("Track", newValue);
                break;
            case 7:
                std::cout << "Restoring original values..." << std::endl;
                restoreMetadata(mediaFile, originalMetadata);
                break;
            case 0:
                std::cout << "Exiting editing..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }

        if (choice != 0 && choice != 7) {
            mediaFile.setMetadata(metadata);
            std::cout << "Metadata updated successfully." << std::endl;
            printMetadata(metadata);
        }
    } while (choice != 0);
}

int main() {
    const std::string mediaDir = "/home/tienck/Documents/Music"; // Change this to your music directory
    int choice;

    do {
        std::cout << "\nChoose an option:" << std::endl;
        std::cout << "1. Show All Files in Music Folder" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            showAllFiles(mediaDir);

            std::cout << "\nEnter the number of the file you want to edit: ";
            int fileChoice;
            std::cin >> fileChoice;
            std::cin.ignore();

            int currentIndex = 1;
            std::string filepath;
            for (const auto& entry : fs::directory_iterator(mediaDir)) {
                if (fs::is_regular_file(entry)) {
                    if (currentIndex == fileChoice) {
                        filepath = entry.path().string();
                        break;
                    }
                    currentIndex++;
                }
            }

            if (!filepath.empty()) {
                try {
                    MediaFile mediaFile(filepath, filepath, "audio");
                    editMetadata(mediaFile);
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            } else {
                std::cerr << "Invalid file choice." << std::endl;
            }
        }
    } while (choice != 0);

    return 0;
}
