#include "ScanfOptionController.hpp"
#include "ControllerManager.hpp"
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

void ScanfOptionController::handleInput() {
    modelManager.getMediaLibrary().clearScreen();
    const std::string filename = "dataUser.txt";

    // Sử dụng hàm từ ControllerManager
    auto data = ControllerManager::readDataFromFile(filename);
    std::string defaultDirectory = data["defaultDirectory"];

    auto* scanOptionView = dynamic_cast<ViewScanfOption*>(viewManager.getView("ViewScanfOption"));
    if (!scanOptionView) {
        std::cerr << "ViewScanfOption not found." << std::endl;
        return;
    }

    // Hiển thị thư mục mặc định hiện tại
    if (defaultDirectory.empty()) {
        scanOptionView->update("Default directory is empty.");
    } else {
        scanOptionView->update("Default directory: " + defaultDirectory);
    }

    while (true) {
        // Hiển thị menu tùy chọn
        std::cout << "1. Add or update default directory\n";
        std::cout << "2. Use default directory\n";
        std::cout << "3. Enter custom directory path\n";
        std::cout << "4. Scan USB devices\n";
        std::cout << "Enter your choice (1-4): ";

        int choiceInput;
        std::cin >> choiceInput;

        auto choice = static_cast<ScanOption>(choiceInput);

        switch (choice) {
            case ScanOption::AddOrUpdateDefaultDir: {
                std::cout << "Enter the new default directory path: ";
                std::string newPath;
                std::cin >> newPath;

                if (std::filesystem::exists(newPath) && std::filesystem::is_directory(newPath)) {
                    defaultDirectory = newPath;
                    data["defaultDirectory"] = defaultDirectory;
                    ControllerManager::writeDataToFile(filename, data);
                    modelManager.getMediaLibrary().scanDirectory(defaultDirectory);
                    scanOptionView->update("Default directory updated: " + defaultDirectory);
                } else {
                    scanOptionView->update("Error: Invalid directory path.");
                }
                break;
            }
            case ScanOption::UseDefaultDir: {
                if (defaultDirectory.empty()) {
                    scanOptionView->update("No default directory set. Returning to menu.");
                } else {
                    scanOptionView->update("Using default directory: " + defaultDirectory);
                    modelManager.getMediaLibrary().scanDirectory(defaultDirectory);
                }
                break;
            }
            case ScanOption::EnterCustomDir: {
                std::cout << "Enter the directory path to scan: ";
                std::string customPath;
                std::cin >> customPath;

                if (std::filesystem::exists(customPath) && std::filesystem::is_directory(customPath)) {
                    modelManager.getMediaLibrary().scanDirectory(customPath);
                    scanOptionView->update("Scanned custom directory: " + customPath);
                } else {
                    scanOptionView->update("Error: Invalid directory path.");
                }
                break;
            }
            case ScanOption::ScanUSB: {
                scanOptionView->update("Scanning USB devices...");
                modelManager.getMediaLibrary().scanUSBDevice();
                scanOptionView->update("USB scanning completed.");
                break;
            }
            default:
                scanOptionView->update("Invalid choice. Please select again.");
                break;
        }

        if (choice >= ScanOption::AddOrUpdateDefaultDir && choice <= ScanOption::ScanUSB) {
            break;
        }
    }
}
