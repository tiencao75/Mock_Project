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

        // Yêu cầu người dùng chọn USB (Cấp 1)
        std::cout << "Select a USB device to scan (enter number): ";
        int selection1;
        std::cin >> selection1;

        // Kiểm tra lựa chọn hợp lệ
        if (selection1 < 1 || selection1 > usbDevices.size())
        {
            std::cerr << "Invalid selection. Please try again." << std::endl;
            return;
        }

        // Lấy đường dẫn USB được chọn (Cấp 1)
        std::string selectedUSB = usbDevices[selection1 - 1];
        std::cout << "You selected: " << selectedUSB << std::endl;

        // Liệt kê thư mục con bên trong thiết bị USB (Cấp 2)
        std::vector<std::string> subFolders;
        for (const auto &entry : std::filesystem::directory_iterator(selectedUSB))
        {
            if (std::filesystem::is_directory(entry))
            {
                subFolders.push_back(entry.path().string());
            }
        }

        // Kiểm tra nếu không tìm thấy thư mục con
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

        // Yêu cầu người dùng chọn thư mục con (Cấp 2)
        std::cout << "Select a subfolder to scan (enter number): ";
        int selection2;
        std::cin >> selection2;

        // Kiểm tra lựa chọn hợp lệ
        if (selection2 < 1 || selection2 > subFolders.size())
        {
            std::cerr << "Invalid selection. Please try again." << std::endl;
            return;
        }

        // Lấy đường dẫn thư mục con được chọn (Cấp 2)
        std::string selectedFolder = subFolders[selection2 - 1];
        std::cout << "Scanning folder: " << selectedFolder << std::endl;

        // Xóa danh sách file cũ trước khi quét
        MediaFiles.clear();

        // Duyệt qua các file trong thư mục con được chọn
        for (const auto &entry : std::filesystem::directory_iterator(selectedFolder))
        {
            if (std::filesystem::is_regular_file(entry))
            {
                std::string extension = entry.path().extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                // Chỉ xử lý các file .mp3 hoặc .mp4
                if (extension == ".mp3" || extension == ".mp4")
                {
                    std::cout << "Found file: " << entry.path() << std::endl;

                    // Tạo đối tượng MediaFile và thêm vào danh sách
                    auto mediaFile = std::make_shared<MediaFile>(
                        entry.path().filename().string(),
                        entry.path().string(),
                        (extension == ".mp3") ? "audio" : "video");
                    MediaFiles.push_back(mediaFile);
                }
            }
        }

        // Hiển thị kết quả quét
        if (MediaFiles.empty())
        {
            std::cout << "No MP3/MP4 files found in the selected folder." << std::endl;
        }
        else
        {
            std::cout << "Scan completed. Found " << MediaFiles.size() << " MP3/MP4 files:" << std::endl;
            for (const auto &file : MediaFiles)
            {
                std::cout << "- " << file->getName() << " (" << file->getType() << ")" << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error while scanning USB: " << e.what() << std::endl;
    }
}