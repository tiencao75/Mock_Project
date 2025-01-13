#include "MediaLibrary.hpp"
#include <algorithm>
#include <stdexcept>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

const std::map<unsigned int, std::shared_ptr<MediaFile>> &MediaLibrary::getAllMediaFiles() const
{
    return mediaFiles;
}

void MediaLibrary::addMediaFile(int index, const std::shared_ptr<MediaFile> &file)
{
    mediaFiles[index] = file;
}

void MediaLibrary::removeMediaFile(unsigned int index)
{
    // Kiểm tra nếu key (index) tồn tại trong map
    auto it = mediaFiles.find(index);
    if (it == mediaFiles.end())
    {
        // Nếu không tìm thấy key, ném ra lỗi
        throw std::runtime_error("Media file with the given index does not exist.");
    }

    // Nếu tìm thấy, xóa phần tử
    mediaFiles.erase(it);
    std::cout << "Media file with index " << index << " has been removed successfully." << std::endl;
}

std::shared_ptr<MediaFile> MediaLibrary::getMediaFileByIndex(unsigned int index) const
{
    auto it = mediaFiles.find(index);
    if (it != mediaFiles.end())
    {
        return it->second; // Trả về giá trị (std::shared_ptr<MediaFile>)
    }
    throw std::out_of_range("Index not found in mediaFiles.");
}

void MediaLibrary::scanDirectory(const std::string &directory)
{
    namespace fs = std::filesystem;
    unsigned int index = mediaFiles.empty() ? 1 : mediaFiles.rbegin()->first + 1;

    try
    {
        // Kiểm tra nếu thư mục tồn tại
        if (!fs::exists(directory) || !fs::is_directory(directory))
        {
            throw std::runtime_error("Error: Path does not exist or is not a directory.");
        }

        // Duyệt qua các file trong thư mục
        for (const auto &entry : fs::directory_iterator(directory))
        {
            if (fs::is_regular_file(entry))
            {
                std::string filePath = entry.path().string();
                std::string fileName = entry.path().filename().string();
                std::string extension = entry.path().extension().string();

                // Chỉ xử lý các file .mp3 hoặc .mp4
                if (extension == ".mp3" || extension == ".mp4")
                {
                    std::string fileType = (extension == ".mp3") ? "audio" : "video";

                    try
                    {
                        // Tạo đối tượng MediaFile
                        auto mediaFile = std::make_shared<MediaFile>(fileName, filePath, fileType);

                        // Tải metadata (giả định rằng Metadata có phương thức setValue)
                        Metadata metadata;
                        metadata.setValue("FileName", fileName);
                        metadata.setValue("FilePath", filePath);
                        metadata.setValue("FileType", fileType);
                        metadata.setValue("FileSize", std::to_string(fs::file_size(filePath)));

                        // Gán metadata vào MediaFile
                        mediaFile->setMetadata(metadata);

                        // Thêm MediaFile vào danh sách
                        mediaFiles[index++] = mediaFile;
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Error loading metadata for file: " << fileName << "\n"
                                  << e.what() << std::endl;
                    }
                }
            }
        }

        std::cout << "Scan completed. Total files added: " << mediaFiles.size() << "\n";
    }
    catch (const std::exception &e)
    {
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