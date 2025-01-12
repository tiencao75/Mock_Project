// #ifndef CONTROLLERMANAGER_HPP
// #define CONTROLLERMANAGER_HPP

// #include "ModelManager.hpp"
// #include "ViewManager.hpp"
// #include "ScanfOptionController.hpp"
// #include "MainMenuController.hpp"

// class ControllerManager {
// private:
//     ModelManager modelManager;
//     ViewManager viewManager;
//     ScanfOptionController scanfOptionController;
//     MainMenuController mainMenuController;

// public:
//     ControllerManager();
//     ~ControllerManager();

//     void handleInputData(); // Xử lý dữ liệu từ người dùng
// };

// #endif // CONTROLLERMANAGER_HPP
#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include "ViewScanfOption.hpp"
#include "ViewMainMenu.hpp"
#include "ScanfOptionController.hpp"
#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include "ScanfOptionController.hpp"
#include "MainMenuController.hpp"
#include "MediaFileController.hpp"
#include "MetadataController.hpp"

enum class MainMenuOption {
    Exit,
    ShowAllMediaFiles,
    ShowMetadata,
    EditMetadata,
    ManagerPlayList
    
};

class ControllerManager {
private:
    ModelManager modelManager;                 // Quản lý block Model
    ViewManager viewManager;                   // Quản lý block View
    ScanfOptionController scanfOptionController; // Quản lý logic quét file
    MainMenuController mainMenuController;     // Quản lý menu chính
    MediaFileController mediaFileController;   // Quản lý logic media file
    MetadataController metadataController;     // Quản lý logic metadata

public:
    ControllerManager();
    ~ControllerManager();

    void handleInputData(); // Xử lý dữ liệu từ người dùng và điều hướng logic
    ModelManager& getModelManager();               // Getter cho ModelManager
    ViewManager& getViewManager();                 // Getter cho ViewManager
    // Hàm đọc và ghi dữ liệu
    static std::map<std::string, std::string> readDataFromFile(const std::string& filename);
    static void writeDataToFile(const std::string& filename, const std::map<std::string, std::string>& data);

};

#endif // CONTROLLERMANAGER_HPP
