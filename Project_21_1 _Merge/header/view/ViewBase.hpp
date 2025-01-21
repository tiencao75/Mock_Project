#ifndef VIEWBASE_HPP
#define VIEWBASE_HPP

#include <string>
#include <iostream>
#include <limits>

class ViewBase {
public:
    virtual ~ViewBase() = default;

    virtual void show() = 0;           // Hiển thị giao diện
    void hide();          // Ẩn giao diện
    void pauseScreen();          //Tam dung man hinh
    virtual void update(const std::string& data) = 0; // Cập nhật dữ liệu hiển thị
    virtual std::string getName() const = 0;          // Lấy tên của view
};

#endif // VIEWBASE_HPP
