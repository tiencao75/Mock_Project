#ifndef VIEWSCANFOPTION_H
#define VIEWSCANFOPTION_H

#include "ViewBase.hpp"
#include <string>

class ViewScanfOption : public ViewBase
{
public:
    void showScanMenu();
    std::string getDirectoryInput();
    void show() override;
    void hide() override;
    void handleInput(const std::string &input) override;
};

#endif // VIEWSCANFOPTION_H