#include "ScanfOptionController.hpp"
#include "FileController.hpp"
#include <iostream>

// Constructor
ScanfOptionController::ScanfOptionController(ControllerManager* manager)
    : controllerManager(manager) {
    // Khởi tạo với controllerManager để truy cập các controller khác
}

// Destructor
ScanfOptionController::~ScanfOptionController() {
    // Dọn dẹp tài nguyên nếu cần thiết, không có tài nguyên cụ thể cần dọn dẹp trong trường hợp này
}

// Hiển thị các tùy chọn quét cho người dùng
void ScanfOptionController::showScanOptions() {
    std::cout << "======= Scan Options =======" << std::endl;
    std::cout << "1. Scan directory" << std::endl;
    std::cout << "2. Scan USB" << std::endl;
    std::cout << "Select: ";
}

// Xử lý quét thư mục
void ScanfOptionController::processDirectoryInput(const std::string& path) {
    std::cout << "Scanning directory: " << path << std::endl;
    // Gọi phương thức scanDirectory từ FileController để quét thư mục
    controllerManager->getFileController()->scanDirectory(path);
}

// Xử lý quét USB
void ScanfOptionController::processUSBScan() {
    std::cout << "Scanning USB..." << std::endl;
    // Gọi phương thức scanUSBDevice từ FileController để quét USB
    controllerManager->getFileController()->scanUSBDevice();
}
