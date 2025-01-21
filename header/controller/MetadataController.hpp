// #endif // METADATACONTROLLER_HPP
#ifndef METADATACONTROLLER_HPP
#define METADATACONTROLLER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include "MediaFile.hpp"
#include "ViewMetadata.hpp"
#include <map>
#include <string>

enum class MetadataOption {
    Exit,
    Title,
    Artist,
    Album,
    Genre,
    Year,
    Track,
    Restore
    
};

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
