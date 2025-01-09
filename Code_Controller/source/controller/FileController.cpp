#include "FileController.hpp"
#include "MediaLibrary.hpp"
#include <iostream>

// Constructor
FileController::FileController(ControllerManager* manager)
    : controllerManager(manager) {
    // No initialization needed for now
}

// Destructor
FileController::~FileController() {
    // Cleanup if necessary
}

// Method to scan a directory and return a list of media files
std::vector<MediaFile> FileController::scanDirectory(const std::string& path) {
    // Call MediaLibrary's method to scan a directory
    controllerManager->getModelManager()->getMediaLibrary()->scanDirectory(path);

    // Get the list of media files after the scan
    return controllerManager->getModelManager()->getMediaLibrary()->getAllMediaFiles();
}

// Method to scan a USB device and return a list of media files
std::vector<MediaFile> FileController::scanUSBDevice() {
    // Call MediaLibrary's method to scan the USB device
    controllerManager->getModelManager()->getMediaLibrary()->scanUSBDevice();

    // Get the list of media files after the scan
    return controllerManager->getModelManager()->getMediaLibrary()->getAllMediaFiles();
}
