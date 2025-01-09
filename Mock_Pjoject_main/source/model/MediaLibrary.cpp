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

void MediaLibrary::scanDirectory(const std::string &directory, std::vector<MediaFile> &mediaFiles)
{
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
                        MediaFile mediaFile(fileName, filePath, fileType);

                        // Lấy metadata từ file sử dụng TagLib
                        Metadata metadata;
                        TagLib::FileRef fileRef(filePath.c_str());

                        if (!fileRef.isNull() && fileRef.tag() && fileRef.audioProperties())
                        {
                            TagLib::Tag *tag = fileRef.tag();
                            TagLib::AudioProperties *audioProperties = fileRef.audioProperties();

                            metadata.setValue("Title", tag->title().toCString(true));
                            metadata.setValue("Artist", tag->artist().toCString(true));
                            metadata.setValue("Album", tag->album().toCString(true));
                            metadata.setValue("Year", std::to_string(tag->year()));
                            metadata.setValue("Track", std::to_string(tag->track()));
                            metadata.setValue("Genre", tag->genre().toCString(true));
                            metadata.setValue("Duration", std::to_string(audioProperties->length()));
                            metadata.setValue("Bitrate", std::to_string(audioProperties->bitrate()));
                            metadata.setValue("SampleRate", std::to_string(audioProperties->sampleRate()));
                            metadata.setValue("Channels", std::to_string(audioProperties->channels()));
                        }
                        else
                        {
                            std::cerr << "Warning: Unable to extract metadata for file: " << fileName << std::endl;
                        }

                        // Cập nhật metadata vào MediaFile
                        metadata.setValue("FileName", fileName);
                        metadata.setValue("FilePath", filePath);
                        metadata.setValue("FileType", fileType);
                        metadata.setValue("FileSize", std::to_string(fs::file_size(filePath)));

                        mediaFile.setMetadata(metadata);

                        // Thêm MediaFile vào danh sách
                        mediaFiles.push_back(mediaFile);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Error loading metadata for file: " << fileName << "\n"
                                  << e.what() << std::endl;
                    }
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
  
}

void MediaLibrary::scanUSBDevice()
{
    // Implementation for scanning USB
}
