#ifndef FILECONTROLLER_HPP
#define FILECONTROLLER_HPP

#include "ControllerManager.hpp"
#include <vector>
#include <string>

class FileController {
private:
    ControllerManager* controllerManager;

public:
    // Constructor
    FileController(ControllerManager* manager);

    // Destructor
    ~FileController();

    // Method to scan a directory and return a list of media files
    std::vector<MediaFile> scanDirectory(const std::string& path);

    // Method to scan a USB device and return a list of media files
    std::vector<MediaFile> scanUSBDevice();
};

#endif // FILECONTROLLER_HPP
