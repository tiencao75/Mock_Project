#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "ViewBase.hpp"
#include <vector>
#include <memory>

class ViewManager
{
private:
    std::vector<std::unique_ptr<ViewBase>> views;

public:
    void switchView(ViewBase *view);
    void addView(std::unique_ptr<ViewBase> view);
    void removeView(ViewBase *view);
};

#endif