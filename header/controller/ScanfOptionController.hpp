#ifndef SCANFOPTIONCONTROLLER_HPP
#define SCANFOPTIONCONTROLLER_HPP

#include "ControllerManager.hpp"
#include <string>

class ScanfOptionController {
private:
    ControllerManager* controllerManager;

public:
    ScanfOptionController(ControllerManager* manager);
    ~ScanfOptionController();

    void handleDirectoryScan(); // Xử lý quét thư mục
    void handleUSBScan();       // Xử lý quét USB
};

#endif // SCANFOPTIONCONTROLLER_HPP
