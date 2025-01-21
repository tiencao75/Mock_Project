#ifndef SCANFOPTIONCONTROLLER_HPP
#define SCANFOPTIONCONTROLLER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include <filesystem>

enum class ScanOption {
    AddOrUpdateDefaultDir = 1,
    UseDefaultDir,
    EnterCustomDir,
    ScanUSB
};

class ScanfOptionController {
private:
    ModelManager& modelManager;
    ViewManager& viewManager;

public:
    ScanfOptionController(ModelManager& modelManager, ViewManager& viewManager);
    ~ScanfOptionController();

    // void handleDirectoryScan(); // Xử lý quét thư mục
    void handleUSBScan();       // Xử lý quét USB
    void handleInput(); // Kiểm tra file media
};

#endif // SCANFOPTIONCONTROLLER_HPP
