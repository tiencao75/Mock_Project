#include "MediaLibrary.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<MediaFile> MediaLibrary::getAllMediaFiles()
{
    return mediaFiles;
}

void MediaLibrary::addMediaFile(const MediaFile &file)
{
    mediaFiles.push_back(file);
}

void MediaLibrary::removeMediaFile(const MediaFile &file)
{
    mediaFiles.erase(std::remove(mediaFiles.begin(), mediaFiles.end(), file), mediaFiles.end());
}

MediaFile MediaLibrary::getMediaFileByName(const std::string &name)
{
    for (const auto &file : mediaFiles)
    {
        if (file.getName() == name)
        {
            return file;
        }
    }
    throw std::runtime_error("Media file not found: " + name);
}

void MediaLibrary::scanDirectory(const std::string &directory, std::vector<std::shared_ptr<MediaFile>> &mediaFiles)
{
    try
    {
        for (const auto &entry : fs::directory_iterator(path))
        {
            if (entry.is_regular_file())
            {
                std::string filePath = entry.path().string();
                std::string fileName = entry.path().filename().string();
                std::string fileType;

                // Đoán loại tệp dựa trên đuôi file
                if (filePath.find(".mp3") != std::string::npos)
                {
                    std::string fileType = (extension == ".mp3") ? "audio" : "video";

                    try
                    {
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
                        mediaFiles.push_back(mediaFile);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Error loading metadata for file: " << fileName << "\n"
                                  << e.what() << std::endl;
                    }
                }
                else if (filePath.find(".mp4") != std::string::npos)
                {
                    fileType = "video";
                }
                else
                {
                    fileType = "unknown";
                }

                // Tạo đối tượng MediaFile với constructor có tham số
                MediaFile mediaFile(fileName, filePath, fileType);
                addMediaFile(mediaFile);
            }
        }
        std::cout << "Scan completed for directory: " << path << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error while scanning directory: " << e.what() << std::endl;
    }
}
