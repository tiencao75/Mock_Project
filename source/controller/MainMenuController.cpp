#include "MainMenuController.hpp"
#include <iostream>

MainMenuController::MainMenuController(ControllerManager* manager)
    : controllerManager(manager) {}

MainMenuController::~MainMenuController() {}

void MainMenuController::handleMenuSelection() {
    bool isRunning = true;

    while (isRunning) {
        // Hiển thị menu chính
        controllerManager->getViewManager().getView("ViewMainMenu")->show();

        // Nhận lựa chọn từ người dùng
        std::cout << "Enter your choice: ";
        int selection;
        std::cin >> selection;

        // Xử lý lựa chọn
        switch (selection) {
        case 1:
            std::cout << "Navigating to Scan Options..." << std::endl;
            // Chuyển sang ViewScanfOption và gọi handleDirectoryScan
            controllerManager->getViewManager().switchView(
                controllerManager->getViewManager().getView("ViewScanfOption"));
            controllerManager->getFileController().handleDirectoryScan();
            break;
        case 2:
            std::cout << "Navigating to Play Media..." << std::endl;
            // Logic xử lý chuyển sang Play Media
            break;
        case 3:
            std::cout << "Navigating to Playlist Manager..." << std::endl;
            // Logic xử lý chuyển sang Playlist Manager
            break;
        case 0:
            std::cout << "Exiting application..." << std::endl;
            isRunning = false;
            break;
        default:
            std::cerr << "Invalid option. Please try again." << std::endl;
            break;
        }
    }
}
