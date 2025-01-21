#include "ScanfOptionController.hpp"
#include "ControllerManager.hpp"
#include "ViewScanfOption.hpp"
#include "ExceptionLib.hpp"
#include <iostream>
#include <filesystem>
#include <stdexcept>

ScanfOptionController::ScanfOptionController(ModelManager& modelManager, ViewManager& viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

ScanfOptionController::~ScanfOptionController() {}



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
    viewManager.getCurrentView()->hide();
    const std::string filename = "dataUser.txt";

    // Load data from file
    auto data = ControllerManager::readDataFromFile(filename);
    std::string defaultDirectory = data["defaultDirectory"];

    auto* scanOptionView = dynamic_cast<ViewScanfOption*>(viewManager.getView("ViewScanfOption"));
    if (!scanOptionView) {
        throw std::runtime_error("ViewScanfOption not found.");
    }

    // Display current default directory
    if (defaultDirectory.empty()) {
        scanOptionView->update("Default directory is empty.");
    } else {
        scanOptionView->update("Default directory: " + defaultDirectory);
    }

    while (true) {
        viewManager.getView("ViewScanfOption")->show();
        // viewManager.getCurrentView()->show();
        size_t choice;
        Exception_Handler("Enter your choice (1-4): ", choice, validateScanfMenu);


        bool backToMenu = false; // Thêm cờ quay lại menu
        switch (static_cast<ScanOption>(choice)) {
            case ScanOption::AddOrUpdateDefaultDir: {
                while (true) {
                std::string newPath;
                Exception_Handler("Enter the new default directory path: ", newPath, validatePath, backToMenu);

                if (backToMenu) {
                    break;
                }
                defaultDirectory = newPath;
                data["defaultDirectory"] = defaultDirectory;
                ControllerManager::writeDataToFile(filename, data);
                modelManager.getMediaLibrary().scanDirectory(defaultDirectory);
                scanOptionView->update("Default directory updated: " + defaultDirectory);
                break;
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
                // std::string customPath;
                // Exception_Handler("Enter the directory path to scan: ", customPath, validatePath);

                // modelManager.getMediaLibrary().scanDirectory(customPath);
                // scanOptionView->update("Scanned custom directory: " + customPath);
                while (true) {
                std::string customPath;
                Exception_Handler("Enter the directory path to scan: ", customPath, validatePath, backToMenu);

                if (backToMenu) {
                    break; 
                }
                modelManager.getMediaLibrary().scanDirectory(customPath);
                scanOptionView->update("Scanned custom directory: " + customPath);
                break;
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

        if (static_cast<ScanOption>(choice) >= ScanOption::AddOrUpdateDefaultDir && static_cast<ScanOption>(choice) <= ScanOption::ScanUSB && (backToMenu == false)) {
            break;
        }
    }
}
