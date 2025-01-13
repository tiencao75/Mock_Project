// #ifndef METADATA_HPP
// #define METADATA_HPP

// #include <string>
// #include <map>

// class Metadata {
// private:
//     std::map<std::string, std::string> data;

// public:
//     // Getters
//     std::map<std::string, std::string> getData() const;
//     std::string getValue(const std::string& key) const;

//     // Setters
//     void setData(const std::map<std::string, std::string>& data);
//     void setValue(const std::string& key, const std::string& value);
// };

// #endif // METADATA_HPP
#ifndef METADATA_HPP
#define METADATA_HPP

#include <string>
#include <map>

class Metadata {
private:
    std::map<std::string, std::string> data;

public:
    // Get all metadata as a key-value map
    std::map<std::string, std::string> getData() const;

    // Get a specific metadata value by key
    std::string getValue(const std::string& key) const;

    // Set all metadata
    void setData(const std::map<std::string, std::string>& data);

    // Set a specific metadata key-value pair
    void setValue(const std::string& key, const std::string& value);

    // Load metadata from a media file
    void loadFromFile(const std::string& filePath);

    // Save metadata back to a media file
    void saveToFile(const std::string& filePath) const;
};

#endif // METADATA_HPP