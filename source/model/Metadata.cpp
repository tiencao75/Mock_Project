#include "Metadata.hpp"

std::map<std::string, std::string> Metadata::getData() const {
    return data;
}

std::string Metadata::getValue(const std::string& key) const {
    auto it = data.find(key);
    return (it != data.end()) ? it->second : "";
}

void Metadata::setData(const std::map<std::string, std::string>& data) {
    this->data = data;
}

void Metadata::setValue(const std::string& key, const std::string& value) {
    data[key] = value;
}
