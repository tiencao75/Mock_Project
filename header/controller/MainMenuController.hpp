#ifndef MAINMENUCONTROLLER_HPP
#define MAINMENUCONTROLLER_HPP

#include "ControllerManager.hpp"

class MainMenuController {
private:
    ControllerManager* controllerManager;

public:
    MainMenuController(ControllerManager* manager);
    ~MainMenuController();

    void handleMenuSelection(); // Tự động hiển thị và xử lý lựa chọn menu
};

#endif // MAINMENUCONTROLLER_HPP

