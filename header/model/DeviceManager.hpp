#ifndef DEVICE_MANAGER_HPP
#define DEVICE_MANAGER_HPP

#include <string>
#include "S32K144Interface.hpp"

class DeviceManager {
private:
    int volume;
    S32K144Interface* s32k144Connection;

public:
    // Constructor
    DeviceManager(S32K144Interface* connection);

    // Destructor
    ~DeviceManager();

    // Set the volume level
    void setVolume(int level);

    // Get the current volume level
    int getVolume() const;

    // Update the display with information
    void updateDisplay(const std::string& info);
};

#endif // DEVICE_MANAGER_HPP
