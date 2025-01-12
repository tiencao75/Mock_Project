#include "MediaLibrary.hpp"
#include <algorithm>
#include <stdexcept>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::vector<std::shared_ptr<MediaFile>> MediaLibrary::getAllMediaFiles() const
{
    return MediaFiles;
}

void MediaLibrary::addMediaFile(const std::shared_ptr<MediaFile> &file)
{
    MediaFiles.push_back(file);
}

void MediaLibrary::removeMediaFile(const std::shared_ptr<MediaFile> &file)
{
    MediaFiles.erase(remove(MediaFiles.begin(), MediaFiles.end(), file), MediaFiles.end());
}

std::shared_ptr<MediaFile> MediaLibrary::getMediaFileByName(const std::string &name) const
{
    for (const auto &file : MediaFiles)
    {
        if (file->getName() == name)
        {
            return file;
        }
    }
    throw std::runtime_error("File not found");
}

void MediaLibrary::scanDirectory(const std::string &directory) {
    try {
        // Xóa danh sách cũ trước khi quét thư mục
        MediaFiles.clear();

        // Kiểm tra nếu thư mục tồn tại
        if (!fs::exists(directory) || !fs::is_directory(directory)) {
            throw std::runtime_error("Error: Path does not exist or is not a directory.");
        }

        // Duyệt qua các file trong thư mục
        for (const auto &entry : fs::directory_iterator(directory)) {
            if (fs::is_regular_file(entry)) {
                std::string filePath = entry.path().string();
                std::string fileName = entry.path().filename().string();
                std::string extension = entry.path().extension().string();

                // Chỉ xử lý các file .mp3 hoặc .mp4
                if (extension == ".mp3" || extension == ".mp4") {
                    std::string fileType = (extension == ".mp3") ? "audio" : "video";

                    try {
                        // Tạo đối tượng MediaFile
                        auto mediaFile = std::make_shared<MediaFile>(fileName, filePath, fileType);

                        // Tải và lưu metadata
                        Metadata metadata;
                        metadata.loadFromFile(filePath);
                        metadata.setValue("FileName", fileName);
                        metadata.setValue("FilePath", filePath);
                        metadata.setValue("FileType", fileType);
                        metadata.setValue("FileSize", std::to_string(fs::file_size(filePath)));

                        // Gán metadata vào MediaFile
                        mediaFile->setMetadata(metadata);

                        // Thêm MediaFile vào danh sách
                        MediaFiles.push_back(mediaFile);
                    } catch (const std::exception &e) {
                        std::cerr << "Error loading metadata for file: " << fileName << "\n"
                                  << e.what() << std::endl;
                    }
                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error while scanning directory: " << e.what() << std::endl;
    }
}

void MediaLibrary::scanUSBDevice()
{
    try {
        // Thư mục mount USB mặc định
        std::string mountBase = "/media/hieuphan";
        std::vector<std::string> usbDevices;

        // Liệt kê các thiết bị USB trong thư mục mount
        for (const auto& entry : std::filesystem::directory_iterator(mountBase)) {
            if (std::filesystem::is_directory(entry)) {
                usbDevices.push_back(entry.path().string());
            }
        }

        if (usbDevices.empty()) {
            std::cerr << "No USB devices found or mounted." << std::endl;
            return;
        }

        // Hiển thị danh sách thiết bị USB
        std::cout << "Available USB devices:\n";
        for (size_t i = 0; i < usbDevices.size(); ++i) {
            std::cout << i + 1 << ". " << usbDevices[i] << std::endl;
        }

        // Cho phép người dùng chọn thiết bị
        std::cout << "Select a USB device to scan (enter number): ";
        int selection;
        std::cin >> selection;

        if (selection < 1 || selection > usbDevices.size()) {
            std::cerr << "Invalid selection." << std::endl;
            return;
        }

        // Lấy đường dẫn USB đã chọn
        std::string selectedUSB = usbDevices[selection - 1];
        std::cout << "Scanning USB at: " << selectedUSB << std::endl;

        // Quét thư mục của USB đã chọn
        MediaFiles.clear(); // Xoá danh sách file cũ
        for (const auto& entry : std::filesystem::directory_iterator(selectedUSB)) {
            if (std::filesystem::is_regular_file(entry)) {
                std::string extension = entry.path().extension().string();
                if (extension == ".mp3" || extension == ".mp4") {
                    std::cout << "Found file: " << entry.path() << std::endl;

                    // Thêm file vào danh sách MediaFiles (nếu cần lưu trữ)
                    auto mediaFile = std::make_shared<MediaFile>(
                        entry.path().filename().string(),
                        entry.path().string(),
                        (extension == ".mp3") ? "audio" : "video"
                    );
                    MediaFiles.push_back(mediaFile);
                }
            }
        }

        if (MediaFiles.empty()) {
            std::cout << "No MP3/MP4 files found on the selected USB." << std::endl;
        } else {
            std::cout << "Scan completed. Found " << MediaFiles.size() << " MP3/MP4 files." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error while scanning USB: " << e.what() << std::endl;
    }
}