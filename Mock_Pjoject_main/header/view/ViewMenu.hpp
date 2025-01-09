#ifndef VIEWMENU_H
#define VIEWMENU_H

#include "ViewBase.hpp"
#include <iostream>
#include <string>

class ViewMenu : public ViewBase
{
public:
    void show() override;
    void hide() override;
    void handleInput(const std::string &input) override;
};

#endif