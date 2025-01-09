#include "MainMenuController.hpp"
#include "ViewMainMenu.hpp"
#include <iostream>

MainMenuController::MainMenuController(ModelManager& modelManager, ViewManager& viewManager)
    : modelManager(modelManager), viewManager(viewManager) {}

MainMenuController::~MainMenuController() {}

void MainMenuController::showMainMenu() {
    auto* mainMenuView = dynamic_cast<ViewMainMenu*>(viewManager.getView("ViewMainMenu"));

    if (mainMenuView) {
        mainMenuView->showMainMenu();
    }

    int selection;
    std::cin >> selection;

    switch (selection) {
    case 1:
        if (mainMenuView) {
            mainMenuView->update("Navigating to File Controller...");
        }
        // Logic xử lý cho File Controller
        break;
    case 2:
        if (mainMenuView) {
            mainMenuView->update("Navigating to Media File Controller...");
        }
        // Logic xử lý cho Media File Controller
        break;
    case 3:
        if (mainMenuView) {
            mainMenuView->update("Navigating to Metadata Controller...");
        }
        // Logic xử lý cho Metadata Controller
        break;
    case 0:
        if (mainMenuView) {
            mainMenuView->update("Exiting application...");
        }
        break;
    default:
        if (mainMenuView) {
            mainMenuView->update("Invalid option. Please try again.");
        }
        break;
    }
}
