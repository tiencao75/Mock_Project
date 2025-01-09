#ifndef SCANFOPTIONCONTROLLER_HPP
#define SCANFOPTIONCONTROLLER_HPP

#include "ControllerManager.hpp"
#include <string>

class ScanfOptionController {
private:
    ControllerManager* controllerManager;

public:
    // Constructor
    ScanfOptionController(ControllerManager* manager);

    // Destructor
    ~ScanfOptionController();

    // Phương thức để hiển thị các tùy chọn quét
    void showScanOptions();

    // Phương thức để xử lý quét thư mục
    void processDirectoryInput(const std::string& path);

    // Phương thức để xử lý quét USB
    void processUSBScan();
};

#endif // SCANFOPTIONCONTROLLER_HPP
