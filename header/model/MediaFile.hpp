#ifndef MEDIAFILE_HPP
#define MEDIAFILE_HPP

#include "Metadata.hpp"
#include <string>

class MediaFile {
private:
    std::string name;
    std::string path;
    std::string type;
    Metadata metadata;
     int duration;

public:
    // Constructor
    MediaFile(const std::string& name, const std::string& path, const std::string& type);

    // Getters
    std::string getName() const;
    std::string getPath() const;
    std::string getType() const;
    Metadata getMetadata() const;
    int getDuration();
    

    // Setters
    void setMetadata(const Metadata& metadata);
    void setType(const std::string& type);
    void setDuration(int duration);
    // Toán tử so sánh ==
    bool operator==(const MediaFile& other) const;

    // Toán tử so sánh != nếu cần
    bool operator!=(const MediaFile& other) const;
};

#endif // MEDIAFILE_HPP
