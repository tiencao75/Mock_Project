#ifndef MAINMENUCONTROLLER_HPP
#define MAINMENUCONTROLLER_HPP

#include "ControllerManager.hpp"

class MainMenuController {
private:
    ControllerManager* controllerManager;

public:
    // Constructor
    MainMenuController(ControllerManager* manager);

    // Destructor
    ~MainMenuController();

    // Method to display the main menu
    void showMainMenu();

    // Method to handle user menu selection
    void handleMenuSelection(int option);
};

#endif // MAINMENUCONTROLLER_HPP
