#ifndef MEDIA_FILE_HPP
#define MEDIA_FILE_HPP

#include <string>
#include "Metadata.hpp"

class MediaFile {
private:
    std::string name;
    std::string path;
    std::string type;
    Metadata metadata;

public:
    MediaFile(const std::string& name, const std::string& path, const std::string& type);

    // Getters
    std::string getName() const;
    std::string getPath() const;
    std::string getType() const;
    Metadata getMetadata() const;

    // Setters
    void setMetadata(const Metadata& metadata);
    void setType(const std::string& type);
        // Toán tử so sánh ==
    bool operator==(const MediaFile& other) const;

    // Toán tử so sánh != nếu cần
    bool operator!=(const MediaFile& other) const;
};

#endif // MEDIA_FILE_HPP
