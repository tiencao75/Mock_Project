#ifndef VIEWMETADATA_H
#define VIEWMETADATA_H

#include "ViewBase.hpp"
#include <map>
#include <string>

class ViewMetadata : public ViewBase
{
public:
    void showFileMetadata(const std::map<std::string, std::string> &metadata);
    void editFileMetadata(std::map<std::string, std::string> &metadata, const std::string &key, const std::string &newValue);
    void show() override;
    void hide() override;
    void handleInput(const std::string &input) override;
};

#endif