

#ifndef VIEWBASE_H
#define VIEWBASE_H

#include <string>

class ViewBase
{
public:
    virtual void show() = 0;                                // Pure virtual method
    virtual void hide() = 0;                                // Pure virtual method
    virtual void handleInput(const std::string &input) = 0; // Pure virtual method
    virtual ~ViewBase() = default;
};

#endif