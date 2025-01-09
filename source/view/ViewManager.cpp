#include "ViewManager.hpp"
#include <iostream>

ViewManager::ViewManager() : currentView(nullptr) {}

ViewManager::~ViewManager() {}

void ViewManager::addView(std::unique_ptr<ViewBase> view) {
    views.push_back(std::move(view));
}

ViewBase* ViewManager::getView(const std::string& name) {
    for (const auto& view : views) {
        if (view->getName() == name) {
            return view.get();
        }
    }
    return nullptr;
}

void ViewManager::switchView(ViewBase* view) {
    if (currentView) {
        currentView->hide();
    }
    currentView = view;
    if (currentView) {
        currentView->show();
    }
}

ViewBase* ViewManager::getCurrentView() {
    return currentView;
}
