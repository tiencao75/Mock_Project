#include "ScanfOptionController.hpp"
#include "ViewScanfOption.hpp"
#include <iostream>

ScanfOptionController::ScanfOptionController(ModelManager& modelManager, ViewManager& viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

ScanfOptionController::~ScanfOptionController() {}

void ScanfOptionController::handleDirectoryScan() {
    auto* scanOptionView = dynamic_cast<ViewScanfOption*>(viewManager.getView("ViewScanfOption"));

    if (scanOptionView) {
        scanOptionView->update("Enter directory path:");
    }

    std::string path;
    std::cin >> path;

    modelManager.getMediaLibrary().scanDirectory(path);

    if (scanOptionView) {
        scanOptionView->update("Scan completed for directory: " + path);
    }
}

void ScanfOptionController::handleUSBScan() {
    auto* scanOptionView = dynamic_cast<ViewScanfOption*>(viewManager.getView("ViewScanfOption"));

    if (scanOptionView) {
        scanOptionView->update("Scanning USB device...");
    }

    modelManager.getMediaLibrary().scanUSBDevice();

    if (scanOptionView) {
        scanOptionView->update("USB scan completed.");
    }
}

bool ScanfOptionController::checkMediaFiles() {
    //auto& mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();
    //return !mediaFiles.empty();
    return 1;
}
// bool ScanfOptionController::checkMediaFiles() {
//     // Hiển thị thông báo yêu cầu nhập đường dẫn
//     std::cout << "Enter the path to scan for media files: ";
//     std::string path;
//     std::cin >> path;

//     // Quét thư mục tại đường dẫn được nhập
//     modelManager.getMediaLibrary().scanDirectory(path);

//     // Lấy danh sách file media sau khi quét
//     auto& mediaFiles = modelManager.getMediaLibrary().getAllMediaFiles();

//     // Kiểm tra danh sách file có trống hay không
//     if (mediaFiles.empty()) {
//         std::cout << "No media files found in the specified directory." << std::endl;
//         return false;
//     }

//     std::cout << "Media files found in the specified directory." << std::endl;
//     return true;
// }