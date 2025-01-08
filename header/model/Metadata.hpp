#ifndef METADATA_HPP
#define METADATA_HPP

#include <string>
#include <map>

class Metadata {
private:
    std::map<std::string, std::string> data;

public:
    // Getters
    std::map<std::string, std::string> getData() const;
    std::string getValue(const std::string& key) const;

    // Setters
    void setData(const std::map<std::string, std::string>& data);
    void setValue(const std::string& key, const std::string& value);
};

#endif // METADATA_HPP
