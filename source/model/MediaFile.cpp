#include "MediaFile.hpp"


MediaFile::MediaFile(const std::string& name, const std::string& path, const std::string& type)
    : name(name), path(path), type(type) {
    metadata.loadFromFile(path); // Automatically load metadata
}

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

void MediaFile::setMetadata(const Metadata& metadata) {
    this->metadata = metadata;
    metadata.saveToFile(path); // Save updated metadata to file
}

void MediaFile::setType(const std::string& type) {
    this->type = type;
}
void MediaFile::setDuration(int duration) {
    this->duration = duration;
}

int MediaFile::getDuration() {
      if (duration > 0) {
        return duration; // Trả về nếu đã được thiết lập
    }

    // Lệnh FFmpeg để lấy thông tin thời lượng
    std::string command = "ffprobe -i \"" + path + "\" -show_entries format=duration -v quiet -of csv=\"p=0\"";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        fprintf(stderr, "Failed to execute ffprobe command.\n");

        return 0;
    }

    char buffer[128];
    std::string result = "";
    while (fgets(buffer, 128, pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    // Xử lý kết quả để lấy thời lượng
    try {
        duration = static_cast<int>(std::stod(result)); // Chuyển đổi chuỗi thành số
    } catch (const std::exception& e) {
        fprintf(stderr, "Failed to execute ffprobe command.\n");

        duration = 0;
    }

    return duration;
}
// Toán tử so sánh ==
bool MediaFile:: operator==(const MediaFile& other) const {
    return this->name == other.name;
}

// Toán tử so sánh != nếu cần
bool MediaFile:: operator!=(const MediaFile& other) const {
    return !(*this == other);
}
