extern "C" {
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
}

#include "MediaFile.hpp"
#include <iostream>
#include <string>
#include <filesystem>

// Constructor
MediaFile::MediaFile(const std::string &name, const std::string &path, const std::string &type)
    : name(name), path(path), type(type)
{
    if (type == "audio" || path.find(".mp3") != std::string::npos)
    {
        metadata.loadFromFile(path);
    }
    else if (type == "video" || path.find(".mp4") != std::string::npos)
    {
        metadata.loadFromMp4(path);
    }
}

// Getters
std::string MediaFile::getName() const {
    return name;
}

std::string MediaFile::getPath() const {
    return path;
}

std::string MediaFile::getType() const {
    return type;
}

Metadata MediaFile::getMetadata() const {
    return metadata;
}

int MediaFile::getDuration() {
    // Kiểm tra tệp có tồn tại không
    if (!std::filesystem::exists(path)) {
        std::cerr << "Error: File does not exist: " << path << std::endl;
        return 0;
    }

    AVFormatContext *formatContext = nullptr;

    // Mở tệp media
    if (avformat_open_input(&formatContext, path.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "Error: Could not open file: " << path << std::endl;
        return 0;
    }

    // Lấy thông tin về tệp
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "Error: Could not retrieve stream info for file: " << path << std::endl;
        avformat_close_input(&formatContext);
        return 0;
    }

    // Lấy thời lượng tệp
    if (formatContext->duration != AV_NOPTS_VALUE) {
        int64_t durationInMicroseconds = formatContext->duration;
        duration = static_cast<int>(durationInMicroseconds / AV_TIME_BASE); // Chuyển micro giây sang giây
        // std::cout << "Debug: Duration in seconds = " << duration << std::endl;
    } else {
        std::cerr << "Error: Duration not available (AV_NOPTS_VALUE)." << std::endl;
        duration = 0;
    }

    // Giải phóng tài nguyên
    avformat_close_input(&formatContext);

    return duration;
}

// Setters
void MediaFile::setMetadata(const Metadata &metadata) {
    this->metadata = metadata;
    metadata.saveToFile(path); // Save updated metadata to file
}

void MediaFile::setType(const std::string& type) {
    this->type = type;
}
void MediaFile::setDuration(int duration) {
    this->duration = duration;
}

// Operators
bool MediaFile::operator==(const MediaFile &other) const {
    return this->name == other.name;
}

// Toán tử so sánh != nếu cần
bool MediaFile:: operator!=(const MediaFile& other) const {
    return !(*this == other);
}
