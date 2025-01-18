#ifndef VIEWMANAGER_HPP
#define VIEWMANAGER_HPP

#include "ViewBase.hpp"
#include <vector>
#include <memory>
#include <string>

class ViewManager {
private:
    std::vector<std::unique_ptr<ViewBase>> views;
    ViewBase* currentView;

public:
    ViewManager();
    ~ViewManager();

    void addView(std::unique_ptr<ViewBase> view); // Thêm view vào danh sách
    ViewBase* getView(const std::string& name);   // Lấy view theo tên
    void switchView(ViewBase* view);             // Chuyển đổi sang view khác
    ViewBase* getCurrentView();                  // Lấy view hiện tại
};

#endif // VIEWMANAGER_HPP
