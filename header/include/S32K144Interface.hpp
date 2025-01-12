// S32K144Interface.hpp
#ifndef S32K144INTERFACE_HPP
#define S32K144INTERFACE_HPP

#include <string>

class S32K144Interface {
public:
    // Constructor
    S32K144Interface();

    // Destructor
    virtual ~S32K144Interface();

    // Set the volume on the hardware
    virtual void setVolume(int level) = 0;

    // Update the hardware display
    virtual void updateDisplay(const std::string& info) = 0;
};

#endif // S32K144INTERFACE_HPP