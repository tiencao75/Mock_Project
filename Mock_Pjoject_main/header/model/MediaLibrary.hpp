#ifndef MEDIALIBRARY_HPP
#define MEDIALIBRARY_HPP

#include "MediaFile.hpp"
#include <vector>
#include <string>

class MediaLibrary
{
private:
    std::vector<MediaFile> mediaFiles;

public:
    std::vector<std::shared_ptr<MediaFile>> getAllMediaFiles() const;
    void addMediaFile(const std::shared_ptr<MediaFile> &file);
    void removeMediaFile(const std::shared_ptr<MediaFile> &file);
    std::shared_ptr<MediaFile> getMediaFileByName(const std::string &name) const;
    void scanDirectory(const std::string &directory, std::vector<std::shared_ptr<MediaFile>> &mediaFiles);

    void scanUSBDevice();
};

#endif
