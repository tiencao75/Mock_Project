#ifndef MEDIA_LIBRARY_HPP
#define MEDIA_LIBRARY_HPP

#include <vector>
#include "MediaFile.hpp"

class MediaLibrary {
private:
    std::vector<MediaFile> mediaFiles;

public:
    MediaLibrary();
    const std::vector<MediaFile>& getAllMediaFiles() const;
    void addMediaFile(const MediaFile& file);
    void removeMediaFile(const MediaFile& file);
    MediaFile getMediaFileByName(const std::string& name) const;
    void scanDirectory(const std::string& path);
    void scanUSBDevice();
};

#endif // MEDIA_LIBRARY_HPP
