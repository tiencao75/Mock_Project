#include "ViewManager.hpp"
#include <iostream>
#include <algorithm>
#include <memory>

void ViewManager::switchView(ViewBase *view)
{
    std::cout << "Switching to another view..." << std::endl;
    if (view)
    {
        view->show();
    }
}

void ViewManager::addView(std::unique_ptr<ViewBase> view)
{
    views.emplace_back(std::move(view));
    std::cout << "View added to manager." << std::endl;
}

void ViewManager::removeView(ViewBase *view)
{
    views.erase(std::remove_if(views.begin(), views.end(),
                               [view](const std::unique_ptr<ViewBase> &v)
                               { return v.get() == view; }),
                views.end());
}
