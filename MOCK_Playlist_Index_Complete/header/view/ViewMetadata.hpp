#ifndef VIEWMETADATA_HPP
#define VIEWMETADATA_HPP

#include "ViewBase.hpp"
#include <string>
#include "MediaFile.hpp"

class ViewMetadata : public ViewBase {
public:
    void show() override;
    void hide() override;
    void update(const std::string& data) override;
    std::string getName() const override;

    void showFileMetadata(const MediaFile& file);
    void editFileMetadata(MediaFile& file);
};

#endif // VIEWMETADATA_HPP
