#ifndef MEDIA_FILE_CONTROLLER_HPP
#define MEDIA_FILE_CONTROLLER_HPP

#include "ControllerBase.hpp"
#include <vector>
#include <string>
#include "MediaFile.hpp"

class MediaFileController : public ControllerBase {
public:
    std::vector<MediaFile> getAllMediaFiles();
    MediaFile getMediaFileDetails(const std::string& name);
    void initialize() override;
};

#endif // MEDIA_FILE_CONTROLLER_HPP
