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
}
