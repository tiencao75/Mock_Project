#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "ViewBase.h"
#include <vector>
#include <memory>

class ViewManager
{
private:
    std::vector<std::unique_ptr<ViewBase>> views;

public:
    void showMenu();
    void switchView(ViewBase *view);
    void addView(std::unique_ptr<ViewBase> view);
    void removeView(ViewBase *view);
};

#endif