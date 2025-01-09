#include "ViewMetadata.hpp"
#include <iostream>

void ViewMetadata::showFileMetadata(const std::map<std::string, std::string> &metadata)
{
    std::cout << "Metadata Information:" << std::endl;
    for (const auto &[key, value] : metadata)
    {
        std::cout << key << ": " << value << std::endl;
    }
}

void ViewMetadata::editFileMetadata(std::map<std::string, std::string> &metadata, const std::string &key, const std::string &newValue)
{
    if (metadata.find(key) != metadata.end())
    {
        metadata[key] = newValue;
        std::cout << "Updated " << key << " to: " << newValue << std::endl;
    }
    else
    {
        std::cout << "Key '" << key << "' not found in metadata!" << std::endl;
    }
}
void ViewMetadata::show()
{
    std::cout << "Showing detailed playlist view..." << std::endl;
}

void ViewMetadata::hide()
{
    std::cout << "Hiding detailed playlist view..." << std::endl;
}

void ViewMetadata::handleInput(const std::string &input)
{
    std::cout << "Handling input for detailed playlist view: " << input << std::endl;
}