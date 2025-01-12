#ifndef VIEWSCANFOPTION_HPP
#define VIEWSCANFOPTION_HPP

#include "ViewBase.hpp"
#include <string>

class ViewScanfOption : public ViewBase {
public:
    void show() override;
    void hide() override;
    void update(const std::string& data) override;
    std::string getName() const override;

    void showScanMenu();         // Hiển thị menu quét
    std::string getDirectoryInput(); // Nhận đường dẫn thư mục từ người dùng
};

#endif // VIEWSCANFOPTION_HPP
