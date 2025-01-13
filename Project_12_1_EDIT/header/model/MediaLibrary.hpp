#ifndef MEDIA_LIBRARY_HPP
#define MEDIA_LIBRARY_HPP

#include <vector>
#include <memory>
#include <string>
#include "MediaFile.hpp"

class MediaLibrary
{
private:
    std::map<unsigned int, std::shared_ptr<MediaFile>> mediaFiles;

public:
    const std::map<unsigned int, std::shared_ptr<MediaFile>> &getAllMediaFiles() const;
    void addMediaFile(int index, const std::shared_ptr<MediaFile> &file);
    void removeMediaFile(unsigned int index);
    std::shared_ptr<MediaFile> getMediaFileByIndex(unsigned int index) const;
    void scanDirectory(const std::string &directory);
    void scanUSBDevice();
};

#endif // MEDIA_LIBRARY_HPP