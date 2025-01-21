#include "MediaLibrary.hpp"
#include "ExceptionLib.hpp"
#include <algorithm>
#include <stdexcept>
#include <filesystem>
#include <iostream>

#include <iomanip>

namespace fs = std::filesystem;

// Constructor
MediaLibrary::MediaLibrary() {
    mediaFiles = std::map<unsigned int, std::shared_ptr<MediaFile>>();
    std::cout << "MediaLibrary initialized with an empty mediaFiles map." << std::endl;
}

// Getter for all media files
const std::map<unsigned int, std::shared_ptr<MediaFile>>& MediaLibrary::getAllMediaFiles() const {
    return mediaFiles;
}

// Add a media file
void MediaLibrary::addMediaFile(int index, const std::shared_ptr<MediaFile>& file) {
    try {
        auto result = mediaFiles.emplace(index, file);
        if (!result.second) {
            std::cerr << "Error: Media file with index " << index << " already exists." << std::endl;
        } else {
            std::cout << "Media file added at index: " << index << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception while adding media file: " << e.what() << std::endl;
    }
}

// Remove a media file
void MediaLibrary::removeMediaFile(unsigned int index) {
    auto it = mediaFiles.find(index);
    if (it == mediaFiles.end()) {
        throw std::runtime_error("Media file with the given index does not exist.");
    }
    mediaFiles.erase(it);
    std::cout << "Media file with index " << index << " has been removed successfully." << std::endl;
}



std::shared_ptr<MediaFile> MediaLibrary::getMediaFileByIndex(unsigned int index) const {
    auto it = mediaFiles.find(index);
    if (it != mediaFiles.end()) {
        return it->second; // Trả về shared_ptr<MediaFile>
    }

    throw std::out_of_range("Index not found in mediaFiles.");
}




void MediaLibrary::scanDirectory(const std::string& directory) {
    std::cout << "\n[INFO] Scanning Directory: " << directory << "\n";
    mediaFiles.clear();
    unsigned int index = mediaFiles.empty() ? 1 : mediaFiles.rbegin()->first + 1;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (std::filesystem::is_regular_file(entry)) {
            std::string extension = entry.path().extension().string();
            if (extension == ".mp3" || extension == ".mp4") {
                auto mediaFile = std::make_shared<MediaFile>(
                    entry.path().filename().string(),
                    entry.path().string(),
                    (extension == ".mp3") ? "audio" : "video");
                mediaFiles[index++] = mediaFile;
            }
        }
    }

    // Gọi hàm phân trang để hiển thị danh sách
    displayPaginatedFiles(mediaFiles);
}


void MediaLibrary::scanUSBDevice() {
    try {
        std::string mountBase = "/media";
        std::vector<std::string> usbDevices;

        // Lấy danh sách các USB devices trong /media
        for (const auto& entry : std::filesystem::directory_iterator(mountBase)) {
            if (std::filesystem::is_directory(entry)) {
                usbDevices.push_back(entry.path().string());
            }
        }

        if (usbDevices.empty()) {
            std::cerr << "[ERROR] No USB devices found or mounted in /media.\n";
            return;
        }

        // Hiển thị danh sách các thiết bị USB
        std::cout << "\n[INFO] Available USB Devices:\n";
        for (size_t i = 0; i < usbDevices.size(); ++i) {
            std::cout << " [" << i + 1 << "] " << usbDevices[i] << "\n";
        }

        // Lựa chọn thiết bị USB
        size_t selection = 0;

        Exception_Handler(
            "Select a USB device to scan (enter number): ",
            selection,
            [](const size_t& value) {
                if (value < 1) throw InvalidInputIntegerException();
            }
        );

        // Kiểm tra lựa chọn
        validateScanUSB(selection, usbDevices.size());

        // Đường dẫn USB được chọn
        std::string selectedUSB = usbDevices[selection - 1];
        std::cout << "\n[INFO] You selected USB Device: " << selectedUSB << "\n";

        // Lấy danh sách các thư mục con bên trong USB được chọn
        std::vector<std::string> subFolders;
        for (const auto& entry : std::filesystem::directory_iterator(selectedUSB)) {
            if (std::filesystem::is_directory(entry)) {
                subFolders.push_back(entry.path().string());
            }
        }

        if (subFolders.empty()) {
            std::cerr << "[ERROR] No subfolders found in the selected USB device.\n";
            return;
        }

        // Hiển thị danh sách các thư mục con
        std::cout << "\n[INFO] Available Folders:\n";
        for (size_t i = 0; i < subFolders.size(); ++i) {
            std::cout << " [" << i + 1 << "] " << subFolders[i] << "\n";
        }

        // Lựa chọn thư mục con
        Exception_Handler(
            "Select a folder to scan (enter number): ",
            selection,
            [](const size_t& value) {
                if (value < 1) throw InvalidInputIntegerException();
            }
        );

        // Kiểm tra lựa chọn thư mục con
        validateScanUSB(selection, subFolders.size());

        // Đường dẫn thư mục con được chọn
        std::string selectedFolder = subFolders[selection - 1];
        std::cout << "\n[INFO] You selected Folder: " << selectedFolder << "\n";
        //Xoa bo cac media cu
        mediaFiles.clear();
        // Quét tất cả các file MP3/MP4 trong thư mục con
        unsigned int index = mediaFiles.empty() ? 1 : mediaFiles.rbegin()->first + 1;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(selectedFolder)) {
            try {
                if (std::filesystem::is_regular_file(entry)) {
                    std::string extension = entry.path().extension().string();
                    if (extension == ".mp3" || extension == ".mp4") {
                        auto mediaFile = std::make_shared<MediaFile>(
                            entry.path().filename().string(),
                            entry.path().string(),
                            (extension == ".mp3") ? "audio" : "video"
                        );
                        mediaFiles[index++] = mediaFile;
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "[WARNING] Error accessing: " << entry.path().string() << " - " << e.what() << "\n";
            }
        }

        // Hiển thị danh sách các file media nếu tìm thấy
        if (!mediaFiles.empty()) {
            displayPaginatedFiles(mediaFiles);
        } else {
            std::cout << "[INFO] No MP3/MP4 files found in the selected folder.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Error while scanning USB: " << e.what() << "\n";
    }
}



std::string MediaLibrary::truncateString(const std::string& str, size_t width) {
    if (str.length() > width) {
        return str.substr(0, width - 3) + "...";
    }
    return str;
}



void MediaLibrary::displayPaginatedFiles(const std::map<unsigned int, std::shared_ptr<MediaFile>>& files, size_t pageSize) {
    size_t totalFiles = files.size();
    if (totalFiles == 0) {
        std::cout << "[INFO] No files to display.\n";
        return;
    }

    size_t totalPages = (totalFiles + pageSize - 1) / pageSize; // Tính số trang
    size_t currentPage = 1;

    while (true) {
        system("clear");
        // Tính khoảng file cho trang hiện tại
        size_t startIndex = (currentPage - 1) * pageSize;
        size_t endIndex = std::min(currentPage * pageSize, totalFiles);

        // Hiển thị thông tin trang
        std::cout << "\n[INFO] Page " << currentPage << " of " << totalPages << "\n";
        std::cout << std::string(80, '=') << "\n";
        std::cout << std::left << std::setw(6) << "Index"
                  << std::setw(40) << "File Name"
                  << std::setw(15) << "Extension"
                  << "Type\n";
        std::cout << std::string(80, '-') << "\n";

        // Lấy iterator bắt đầu từ startIndex
        auto it = files.begin();
        std::advance(it, startIndex);

        // Hiển thị file trong trang hiện tại
        for (size_t i = startIndex; i < endIndex; ++i, ++it) {
            const auto& file = it->second;

            // Lấy phần mở rộng từ tên file
            std::string extension = "";
            size_t dotPos = file->getName().find_last_of('.');
            if (dotPos != std::string::npos) {
                extension = file->getName().substr(dotPos);
            }

            std::cout << std::left << std::setw(6) << it->first
                      << std::setw(40) << (file->getName().substr(0, 35) + (file->getName().size() > 35 ? "..." : ""))
                      << std::setw(15) << extension
                      << file->getType() << "\n";
        }
        std::cout << std::string(80, '=') << "\n";

        // Hiển thị tùy chọn điều hướng
        std::cout << "\nNavigation Options:\n";
        if (currentPage > 1) std::cout << " [P] Previous Page\n";
        if (currentPage < totalPages) std::cout << " [N] Next Page\n";
        std::cout << " [Q] Quit\n";
        std::cout << "Enter your choice: ";
        char choice;
        std::cin >> choice;

        if (choice == 'P' || choice == 'p') {
            if (currentPage > 1) --currentPage;
        } else if (choice == 'N' || choice == 'n') {
            if (currentPage < totalPages) ++currentPage;
        } else if (choice == 'Q' || choice == 'q') {
            break;
        } else {
            std::cerr << "[ERROR] Invalid choice. Please try again.\n";
        }
    }
}