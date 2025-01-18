// #ifndef MEDIAFILECONTROLLER_HPP
// #define MEDIAFILECONTROLLER_HPP

// #include "ControllerManager.hpp"
// #include "MediaFile.hpp"
// #include <vector>
// #include <string>

// class MediaFileController {
// private:
//     ControllerManager* controllerManager;

// public:
//     // Constructor
//     MediaFileController(ControllerManager* manager);

//     // Destructor
//     ~MediaFileController();

//     // Method to get all media files
//     std::vector<MediaFile> getAllMediaFiles();

//     // Method to get details of a specific media file by name
//     MediaFile getMediaFileDetails(const std::string& name);
// };

// #endif // MEDIAFILECONTROLLER_HPP
#ifndef MEDIAFILECONTROLLER_HPP
#define MEDIAFILECONTROLLER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include "ViewMediaFile.hpp"
#include "ViewMetadata.hpp"
#include "MediaFile.hpp"
#include <vector>
#include <string>
#include <iostream>

enum class MediaMenuOption {
    BackToMainMenu = 0,
    ShowAllMediaFiles = 1,
    ShowMetadata = 2
};
class MediaFileController {
private:
    ModelManager& modelManager;
    ViewManager& viewManager;

public:
    MediaFileController(ModelManager& modelManager, ViewManager& viewManager);
    ~MediaFileController();

    std::vector<MediaFile> getAllMediaFiles();           // Lấy danh sách tất cả các file media
    MediaFile getMediaFileDetails(unsigned int index); // Lấy chi tiết file media theo ID
    void handleInput();
};

#endif // MEDIAFILECONTROLLER_HPP
