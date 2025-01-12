#include "DeviceManager.hpp"
#include <iostream>

// Constructor
DeviceManager::DeviceManager(){}
DeviceManager::DeviceManager(S32K144Interface* connection)
    : volume(0), s32k144Connection(connection) {}

// Destructor
DeviceManager::~DeviceManager() {
    // If connection is dynamically allocated, release it
    delete s32k144Connection;
}

// Set the volume level
void DeviceManager::setVolume(int level) {
    if (level < 0 || level > 100) {
        std::cerr << "Error: Volume must be between 0 and 100." << std::endl;
        return;
    }
    volume = level;
    if (s32k144Connection) {
        s32k144Connection->setVolume(level); // Assuming S32K144Interface has a method to set volume
    }
}

// Get the current volume level
int DeviceManager::getVolume() const {
    return volume;
}

// Update the display with information
void DeviceManager::updateDisplay(const std::string& info) {
    if (s32k144Connection) {
        s32k144Connection->updateDisplay(info); // Assuming S32K144Interface has a method to send display info
    } else {
        std::cerr << "Error: No S32K144 connection available." << std::endl;
    }
}
