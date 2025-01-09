#ifndef MEDIAFILECONTROLLER_HPP
#define MEDIAFILECONTROLLER_HPP

#include "ControllerManager.hpp"
#include "MediaFile.hpp"
#include <vector>
#include <string>

class MediaFileController {
private:
    ControllerManager* controllerManager;

public:
    // Constructor
    MediaFileController(ControllerManager* manager);

    // Destructor
    ~MediaFileController();

    // Method to get all media files
    std::vector<MediaFile> getAllMediaFiles();

    // Method to get details of a specific media file by name
    MediaFile getMediaFileDetails(const std::string& name);
};

#endif // MEDIAFILECONTROLLER_HPP
