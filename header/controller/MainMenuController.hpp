#ifndef MAINMENUCONTROLLER_HPP
#define MAINMENUCONTROLLER_HPP

#include "ModelManager.hpp"
#include "ViewManager.hpp"

class MainMenuController {
private:
    ModelManager& modelManager;
    ViewManager& viewManager;

public:
    MainMenuController(ModelManager& modelManager, ViewManager& viewManager);
    ~MainMenuController();

    void showMainMenu(); // Hiển thị menu chính và xử lý lựa chọn
};

#endif // MAINMENUCONTROLLER_HPP
