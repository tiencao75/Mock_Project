#ifndef METADATACONTROLLER_HPP
#define METADATACONTROLLER_HPP

#include <string>
#include <map>
#include "MediaFile.h"

class MetadataController {
public:
    std::map<std::string, std::string> getMediaFileMetadata(const MediaFile& file);
    void updateMediaFileMetadata(MediaFile& file, const std::map<std::string, std::string>& metadata);
};

#endif // METADATACONTROLLER_HPP
