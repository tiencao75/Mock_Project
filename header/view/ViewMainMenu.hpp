#ifndef VIEWMAINMENU_HPP
#define VIEWMAINMENU_HPP

#include "ViewBase.hpp"
#include <string>

class ViewMainMenu : public ViewBase {
public:
    void show() override;
    void hide() override;
    void update(const std::string& data) override;
    std::string getName() const override;

    void showMainMenu(); // Hiển thị menu chính
    void handleMenuSelection(int selection); // Xử lý lựa chọn menu
};

#endif // VIEWMAINMENU_HPP
