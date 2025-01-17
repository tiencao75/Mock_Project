// #ifndef METADATACONTROLLER_HPP
// #define METADATACONTROLLER_HPP

// #include "ControllerManager.hpp"
// #include "MediaFile.hpp"
// #include <map>
// #include <string>

// class MetadataController {
// private:
//     ControllerManager* controllerManager;

// public:
//     // Constructor
//     MetadataController(ControllerManager* manager);

//     // Destructor
//     ~MetadataController();

//     // Method to get metadata of a media file
//     std::map<std::string, std::string> getMediaFileMetadata(MediaFile& file);

//     // Method to update metadata of a media file
//     void updateMediaFileMetadata(MediaFile& file, const std::map<std::string, std::string>& metadata);
// };

// #endif // METADATACONTROLLER_HPP
#ifndef METADATACONTROLLER_HPP
#define METADATACONTROLLER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include "MediaFile.hpp"
#include "ViewMetadata.hpp"
#include <map>
#include <string>

class MetadataController {
private:
    ModelManager& modelManager;
    ViewManager& viewManager;

public:
    MetadataController(ModelManager& modelManager, ViewManager& viewManager);
    ~MetadataController();

    std::map<std::string, std::string> getMediaFileMetadata(MediaFile& file); // Lấy metadata của file
    void updateMediaFileMetadata(MediaFile& file, const std::string& key, const std::string& value); // Cập nhật metadata
    void handleInput();
};

#endif // METADATACONTROLLER_HPP
