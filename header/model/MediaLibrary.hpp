#ifndef MEDIA_LIBRARY_HPP
#define MEDIA_LIBRARY_HPP

#include <vector>
#include <memory>
#include <string>
#include "MediaFile.hpp"

class MediaLibrary
{
private:
    std::vector<std::shared_ptr<MediaFile>> MediaFiles;

public:
    std::vector<std::shared_ptr<MediaFile>> getAllMediaFiles() const;
    void addMediaFile(const std::shared_ptr<MediaFile> &file);
    void removeMediaFile(const std::shared_ptr<MediaFile> &file);
    std::shared_ptr<MediaFile> getMediaFileByName(const std::string &name) const;
    void scanDirectory(const std::string &directory);

    void scanUSBDevice();
};

#endif // MEDIA_LIBRARY_HPP