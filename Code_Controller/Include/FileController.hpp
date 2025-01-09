#ifndef FILE_CONTROLLER_HPP
#define FILE_CONTROLLER_HPP

#include "ControllerBase.hpp"
#include <vector>
#include <string>
#include "MediaFile.hpp"

class FileController : public ControllerBase {
public:
    std::vector<MediaFile> scanDirectory(const std::string& path);
    std::vector<MediaFile> scanUSBDevice();
    void initialize() override;
};

#endif // FILE_CONTROLLER_HPP
