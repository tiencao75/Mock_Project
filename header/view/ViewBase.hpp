#ifndef VIEWBASE_HPP
#define VIEWBASE_HPP

#include <string>

class ViewBase {
public:
    virtual ~ViewBase() = default;

    virtual void show() = 0;           // Hiển thị giao diện
    virtual void hide() = 0;           // Ẩn giao diện
    virtual void update(const std::string& data) = 0; // Cập nhật dữ liệu hiển thị
    virtual std::string getName() const = 0;          // Lấy tên của view
};

#endif // VIEWBASE_HPP
