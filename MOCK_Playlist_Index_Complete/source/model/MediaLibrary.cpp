#include "MediaLibrary.hpp"
#include <algorithm>
#include <stdexcept>
#include <filesystem>
#include <iostream>

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

// Get media file by index
std::shared_ptr<MediaFile> MediaLibrary::getMediaFileByIndex(unsigned int index) const {
    auto it = mediaFiles.find(index);
    if (it != mediaFiles.end()) {
        auto mediaFile = it->second;
        std::cout << "Showing metadata for file: " << mediaFile->getName() << std::endl;

        // Display metadata
        Metadata metadata = mediaFile->getMetadata();
        std::map<std::string, std::string> data = metadata.getData();
        for (const auto& [key, value] : data) {
            std::cout << key << ": " << (value.empty() ? "unknown" : value) << std::endl;
        }

        return mediaFile;
    }

    throw std::out_of_range("Index not found in mediaFiles.");
}

// Scan a directory for media files
void MediaLibrary::scanDirectory(const std::string &directory) {
    namespace fs = std::filesystem;
    unsigned int index = mediaFiles.empty() ? 1 : mediaFiles.rbegin()->first + 1;

    try {
        if (!fs::exists(directory) || !fs::is_directory(directory)) {
            throw std::runtime_error("Error: Path does not exist or is not a directory.");
        }

        for (const auto &entry : fs::directory_iterator(directory)) {
            if (fs::is_regular_file(entry)) {
                std::string fileName = entry.path().filename().string();
                std::string filePath = entry.path().string();
                std::string extension = entry.path().extension().string();

                std::cout << "Processing file: " << fileName 
                          << ", Path: " << filePath 
                          << ", Extension: " << extension 
                          << ", Index: " << index << std::endl;

                if (!fs::exists(filePath)) {
                    std::cerr << "Error: File does not exist: " << filePath << std::endl;
                    continue;
                }

                if (extension == ".mp3" || extension == ".mp4") {
                    try {
                        auto mediaFile = std::make_shared<MediaFile>(fileName, filePath, extension == ".mp3" ? "audio" : "video");

                        if (!mediaFile) {
                            std::cerr << "Error: Failed to create MediaFile for " << filePath << std::endl;
                            continue;
                        }

                        auto result = mediaFiles.emplace(index, mediaFile);
                        if (!result.second) {
                            std::cerr << "Error: Failed to insert mediaFile at index: " << index << std::endl;
                        } else {
                            std::cout << "Inserted mediaFile: " << mediaFile->getName() << " at index: " << index << std::endl;
                            ++index;
                        }
                    } catch (const std::exception &e) {
                        std::cerr << "Exception during MediaFile creation or insertion: " << e.what() << std::endl;
                    }
                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error in scanDirectory: " << e.what() << std::endl;
    }
}

void MediaLibrary::scanUSBDevice()
{
    try
    {
        // Đặt thư mục mount mặc định là "/media"
        std::string mountBase = "/media";
        std::vector<std::string> usbDevices;

        // Liệt kê tất cả các thư mục trong "/media"
        for (const auto &entry : std::filesystem::directory_iterator(mountBase))
        {
            if (std::filesystem::is_directory(entry))
            {
                usbDevices.push_back(entry.path().string());
            }
        }

        // Kiểm tra nếu không tìm thấy thiết bị USB nào
        if (usbDevices.empty())
        {
            std::cerr << "No USB devices found or mounted in /media." << std::endl;
            return;
        }

        // Hiển thị danh sách thiết bị USB
        std::cout << "Available USB devices in /media:\n";
        for (size_t i = 0; i < usbDevices.size(); ++i)
        {
            std::cout << i + 1 << ". " << usbDevices[i] << std::endl;
        }

        // Yêu cầu người dùng chọn USB
        std::cout << "Select a USB device to scan (enter number): ";
        int selection1;
        std::cin >> selection1;

        // Kiểm tra lựa chọn hợp lệ
        if (selection1 < 1 || selection1 > usbDevices.size())
        {
            std::cerr << "Invalid selection. Please try again." << std::endl;
            return;
        }

        // Lấy đường dẫn USB được chọn
        std::string selectedUSB = usbDevices[selection1 - 1];
        std::cout << "You selected: " << selectedUSB << std::endl;

        // Duyệt qua các thư mục con
        std::vector<std::string> subFolders;
        for (const auto &entry : std::filesystem::directory_iterator(selectedUSB))
        {
            if (std::filesystem::is_directory(entry))
            {
                subFolders.push_back(entry.path().string());
            }
        }

        // Kiểm tra nếu không có thư mục con
        if (subFolders.empty())
        {
            std::cerr << "No subfolders found in the selected USB device." << std::endl;
            return;
        }

        // Hiển thị danh sách thư mục con
        std::cout << "Available subfolders in " << selectedUSB << ":\n";
        for (size_t i = 0; i < subFolders.size(); ++i)
        {
            std::cout << i + 1 << ". " << subFolders[i] << std::endl;
        }

        // Yêu cầu người dùng chọn thư mục con
        std::cout << "Select a subfolder to scan (enter number): ";
        int selection2;
        std::cin >> selection2;

        // Kiểm tra lựa chọn hợp lệ
        if (selection2 < 1 || selection2 > subFolders.size())
        {
            std::cerr << "Invalid selection. Please try again." << std::endl;
            return;
        }

        // Lấy đường dẫn thư mục con được chọn
        std::string selectedFolder = subFolders[selection2 - 1];
        std::cout << "Scanning folder: " << selectedFolder << std::endl;

        // Quét thư mục con được chọn
        unsigned int index = mediaFiles.empty() ? 1 : mediaFiles.rbegin()->first + 1;
        for (const auto &entry : std::filesystem::directory_iterator(selectedFolder))
        {
            if (std::filesystem::is_regular_file(entry))
            {
                std::string extension = entry.path().extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                // Chỉ xử lý các file .mp3 hoặc .mp4
                if (extension == ".mp3" || extension == ".mp4")
                {
                    auto mediaFile = std::make_shared<MediaFile>(
                        entry.path().filename().string(),
                        entry.path().string(),
                        (extension == ".mp3") ? "audio" : "video");

                    // Thêm MediaFile vào map
                    mediaFiles[index++] = mediaFile;
                }
            }
        }

        // Hiển thị kết quả quét
        if (mediaFiles.empty())
        {
            std::cout << "No MP3/MP4 files found in the selected folder." << std::endl;
        }
        else
        {
            std::cout << "Scan completed. Found " << mediaFiles.size() << " MP3/MP4 files:" << std::endl;
            for (const auto &entry : mediaFiles)
            {
                std::cout << entry.first << ": " << entry.second->getName() << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error while scanning USB: " << e.what() << std::endl;
    }
}