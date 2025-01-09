#include "ScanfOptionController.hpp"
#include <iostream>

ScanfOptionController::ScanfOptionController(ControllerManager* manager)
    : controllerManager(manager) {}

ScanfOptionController::~ScanfOptionController() {}

void ScanfOptionController::handleDirectoryScan() {
    ViewBase* view = controllerManager->getViewManager().getView("ViewScanfOption");
    if (view) {
        std::cout << "Enter directory path: ";
        std::string path;
        std::cin >> path;

        // Gọi ModelManager để quét thư mục
        controllerManager->getModelManager().getMediaLibrary().scanDirectory(path);

        // Hiển thị kết quả
        view->update("Scan completed for directory: " + path);
    } else {
        std::cerr << "View not found!" << std::endl;
    }
}

void ScanfOptionController::handleUSBScan() {
    ViewBase* view = controllerManager->getViewManager().getView("ViewScanfOption");
    if (view) {
        // Gọi ModelManager để quét USB
        controllerManager->getModelManager().getMediaLibrary().scanUSBDevice();

        // Hiển thị kết quả
        view->update("Scan completed for USB device.");
    } else {
        std::cerr << "View not found!" << std::endl;
    }
}

