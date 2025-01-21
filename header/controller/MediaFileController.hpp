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
